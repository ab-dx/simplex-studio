#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    return 1;
  }

  listen(server_fd, 3);

  while (1) {
    int addrlen = sizeof(address);
    int new_socket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    char payload[10 * 1024] = {0};
    read(new_socket, payload, sizeof(payload) - 1);
    printf("--- RECEIVED FROM CLIENT ---\n%s\n----------------------------\n",
           payload);
    // Extract the code
    char *separator = strstr(payload, "\r\n\r\n");
    char *assembly_code = (separator != NULL) ? separator + 4 : "ldc 5\nHALT\n";
    printf("Attempting to compile:\n'%s'\n", assembly_code);

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
      // dup2(asm_to_server[1], STDERR_FILENO);
      close(server_to_asm[0]);
      close(server_to_asm[1]);
      close(asm_to_server[0]);
      close(asm_to_server[1]);

      execl("/home/helix/code/simplex_project/assembler/build/target/asm",
            "/home/helix/code/simplex_project/assembler/build/target/asm", "-i",
            NULL);
      perror("execl failed");
      return 1; // Exit child if execl fails
    } else {
      // PARENT PROCESS
      close(server_to_asm[0]);
      close(asm_to_server[1]);

      // Send code and close write pipe so assembler can finish
      write(server_to_asm[1], assembly_code, strlen(assembly_code));
      int written =
          write(server_to_asm[1], assembly_code, strlen(assembly_code));
      printf("Bytes written to assembler: %d\n", written);
      close(server_to_asm[1]);
      close(server_to_asm[1]);

      // Read the binary response
      char buffer[1024] = {0};
      int count = 0;
      int bytes_read;
      while ((bytes_read = read(asm_to_server[0], buffer + count, 4)) > 0) {
        count += bytes_read;
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
      write(new_socket, headers, header_len);
      write(new_socket, buffer, count);
      waitpid(pid, NULL, 0);

      close(new_socket);
    }
  }

  return 0;
}
