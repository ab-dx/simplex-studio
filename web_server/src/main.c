#include "../include/server.h"

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
    char *payload_copy = malloc(sizeof(payload));
    strcpy(payload_copy, payload);
    char *verb = strtok(payload_copy, " \t\n");
    printf("HTTP Verb: %s\n", verb);

    char *route = strtok(NULL, " \t\n");
    printf("HTTP Route: %s\n", route);

    handle_route(new_socket, verb, route, payload);
  }

  return 0;
}
