#include "../include/server.h"

void assemble_request(char *assembly_code, int socket) {

  int server_to_asm[2];
  int asm_to_server[2];
  pipe(server_to_asm);
  pipe(asm_to_server);

  // Fork a new assembler for this request
  pid_t pid = fork();

  if (pid == 0) {
    // CHILD PROCESS
    dup2(server_to_asm[0], STDIN_FILENO);
    dup2(asm_to_server[1], STDOUT_FILENO);
    dup2(asm_to_server[1], STDERR_FILENO);
    close(server_to_asm[0]);
    close(server_to_asm[1]);
    close(asm_to_server[0]);
    close(asm_to_server[1]);

    execl("/home/helix/code/simplex_project/assembler/build/target/asm",
          "/home/helix/code/simplex_project/assembler/build/target/asm", "-i",
          NULL);
    perror("execl failed");
    exit(1); // Exit child if execl fails
  } else {
    // PARENT PROCESS
    close(server_to_asm[0]);
    close(asm_to_server[1]);

    // Send code and close write pipe so assembler can finish
    // write(server_to_asm[1], assembly_code, strlen(assembly_code));
    int written = write(server_to_asm[1], assembly_code, strlen(assembly_code));
    printf("Bytes written to assembler: %d\n", written);
    close(server_to_asm[1]);
    close(server_to_asm[1]);

    // Read the binary response
    char buffer[100 * 1024] = {0}; // 100kb buffer for program
    int count = 0;
    int bytes_read;
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

    // Format and send HTTP response
    char headers[256];
    int header_len = snprintf(headers, sizeof(headers),
                              "HTTP/1.1 200 OK\r\n"
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
