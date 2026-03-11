#include "../include/server.h"

void emulate_request(char *machine_code, int content_length, int socket) {

  int server_to_emu[2];
  int emu_to_server[2];
  pipe(server_to_emu);
  pipe(emu_to_server);

  // Fork a new emulator for this request
  pid_t pid = fork();

  if (pid == 0) {
    // CHILD PROCESS
    dup2(server_to_emu[0], STDIN_FILENO);
    dup2(emu_to_server[1], STDOUT_FILENO);
    // dup2(emu_to_server[1], STDERR_FILENO);
    close(server_to_emu[0]);
    close(server_to_emu[1]);
    close(emu_to_server[0]);
    close(emu_to_server[1]);

    execl("../assembler/build/target/emu", "../assembler/build/target/emu",
          "-j", NULL);
    perror("execl failed");
    exit(1); // Exit child if execl fails
  } else {
    // PARENT PROCESS
    close(server_to_emu[0]);
    close(emu_to_server[1]);

    // Send code and close write pipe so emulator can finish
    // write(server_to_emu[1], machine_code, content_length);
    int written = write(server_to_emu[1], machine_code, content_length);
    printf("Bytes written to emulator: %d\n", written);
    close(server_to_emu[1]);
    close(server_to_emu[1]);

    // Read the binary response
    char buffer[1000 * 1024] = {0}; // 1000 kb buffer for response
    int count = 0;
    int bytes_read;
    while (count < sizeof(buffer) - 1) { // Don't read more than buffer size
      bytes_read =
          read(emu_to_server[0], buffer + count, sizeof(buffer) - 1 - count);
      if (bytes_read <= 0)
        break;
      count += bytes_read;
      if (count >= sizeof(buffer) - 1) {
        printf("WARNING: Emulator output exceeded buffer limit. Terminating "
               "child process.\n");
        kill(pid, SIGKILL);
        break;
      }
    }
    printf("Bytes read from emulator: %d\n", count);
    close(emu_to_server[0]); // Clean up read pipe

    // Format and send HTTP response
    char headers[256];
    int header_len = snprintf(headers, sizeof(headers),
                              "HTTP/1.1 200 OK\r\n"
                              "Access-Control-Allow-Origin: *\r\n"
                              "Content-Type: application/json\r\n"
                              "Content-Length: %d\r\n"
                              "\r\n",
                              count);
    write(socket, headers, header_len);
    write(socket, buffer, count);
    waitpid(pid, NULL, 0);

    close(socket);
  }
}
