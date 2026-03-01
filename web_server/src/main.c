#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int server_to_asm[2];
  int asm_to_server[2];
  pipe(server_to_asm);
  pipe(asm_to_server);

  pid_t pid = fork();

  if (pid == 0) {
    // Child process

    dup2(server_to_asm[0],
         STDIN_FILENO); // Read end of server to asm overrides stdin
    dup2(asm_to_server[1],
         STDOUT_FILENO); // Write end of asm to server overrides stdout

    // Close background pipes of child process
    close(server_to_asm[0]);
    close(server_to_asm[1]);
    close(asm_to_server[0]);
    close(asm_to_server[1]);

    // Transform child process into assembler
    execl("../assembler/build/target/asm", "../assembler/build/target/asm",
          "-i", NULL);
  } else {
    // Parent process

    // Close unused pipes
    close(server_to_asm[0]);
    close(asm_to_server[1]);

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
      char req[1024] = {0};
      read(new_socket, req, 4);
      printf("%s\n", req);
      char *assembly_code = "ldc 5\nHALT\n";
      write(server_to_asm[1], assembly_code, strlen(assembly_code));
      close(server_to_asm[1]);

      char buffer[1024] = {0};
      int count = 0;
      int bytes_read;
      while ((bytes_read = read(asm_to_server[0], buffer + count, 4)) > 0) {
        count += bytes_read;
      }

      for (int i = 0; i < count; i += 4) {
        printf("%08X\n", *(int *)(buffer + i));
      }
    }
  }

  return 0;
}
