/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
#include "../include/server.h"

void assemble_request(char *assembly_code, int socket) {

  int server_to_asm[2];
  int asm_to_server[2];
  int asm_to_server_err[2];
  pipe(server_to_asm);
  pipe(asm_to_server);
  pipe(asm_to_server_err);

  // Fork a new assembler for this request
  pid_t pid = fork();

  if (pid == 0) {
    // CHILD PROCESS
    // Duplicate the pipe file descriptor to serve as stdin, stdout, stderr for this process
    dup2(server_to_asm[0], STDIN_FILENO);
    dup2(asm_to_server[1], STDOUT_FILENO);
    dup2(asm_to_server_err[1], STDERR_FILENO);
    // Close pipes after assigning std streams
    close(server_to_asm[0]);
    close(server_to_asm[1]);
    close(asm_to_server[0]);
    close(asm_to_server[1]);
    close(asm_to_server_err[0]);
    close(asm_to_server_err[1]);
    // Transform the child process into assembler process
    execl("../assembler/build/target/asm", "../assembler/build/target/asm",
          "-i", NULL);
    perror("execl failed");
    exit(1); // Exit child if execl fails
  } else {
    // PARENT PROCESS
    close(server_to_asm[0]);
    close(asm_to_server[1]);

    // Send code and close write pipe so assembler can finish
    int written = write(server_to_asm[1], assembly_code, strlen(assembly_code));
    printf("Bytes written to assembler: %d\n", written);
    close(server_to_asm[1]);
    close(server_to_asm[1]);
    close(asm_to_server_err[1]);

    // Read the binary response from pipe
    char buffer[500 * 1024] = {0}; // 500kb buffer for program
    int count = 0;
    int bytes_read;
    // Safely read 4 bytes at a time, quit if overflow
    while ((bytes_read = read(asm_to_server[0], buffer + count, 4)) > 0) {
      count += bytes_read;
      if (count >= sizeof(buffer) - 1) {
        printf("WARNING: Assembler output exceeded buffer limit. Terminating "
               "child process.\n");
        kill(pid, SIGKILL);
        break;
      }
    }
    printf("Bytes read from assembler: %d\n", count);
    close(asm_to_server[0]); // Clean up read pipe

    // Check for errors
    char err_buffer[1024] = {0}; // Buffer for stderr output
    int err_count = 0;
    int err_bytes_read;
    while ((err_bytes_read =
                read(asm_to_server_err[0], err_buffer + err_count, 4)) > 0) {
      err_count += err_bytes_read;
      if (err_count >= sizeof(err_buffer) - 1) {
        printf("WARNING: Assembler errors exceeded buffer limit. Terminating "
               "child process.\n");
        kill(pid, SIGKILL);
        break;
      }
    }
    close(asm_to_server_err[0]); // Clean up err read pipe

    printf("ERROR BUFFER: %s", err_buffer);

    if (strncmp(err_buffer,"ERROR",5)==0) {
      // Format and send HTTP response
      char error[1040];
      sprintf(error, "{\"error\": \"%s\"}", err_buffer);
      char headers[256];
      int header_len = snprintf(headers, sizeof(headers),
                                "HTTP/1.1 400 Bad Request\r\n"
                                "Access-Control-Allow-Origin: *\r\n"
                                "Content-Type: application/json\r\n"
                                "Content-Length: %d\r\n"
                                "\r\n",
                                1040);
      write(socket, headers, header_len);
      write(socket, error, 1040);
      waitpid(pid, NULL, 0);

      close(socket);
    } else {
      // Format and send HTTP response
      char headers[256];
      int header_len = snprintf(headers, sizeof(headers),
                                "HTTP/1.1 200 OK\r\n"
                                "Access-Control-Allow-Origin: *\r\n"
                                "Content-Type: application/octet-stream\r\n"
                                "Content-Length: %d\r\n"
                                "\r\n",
                                count);
      write(socket, headers, header_len);
      write(socket, buffer, count);
      waitpid(pid, NULL, 0);

      close(socket);
    }
  }
}
