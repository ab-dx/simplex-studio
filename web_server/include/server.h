#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

void assemble_request(char *assembly_code, int socket);
void emulate_request(char *machine_code, int content_length, int socket);
void handle_route(int socket, char *verb, char *route, char *payload);
