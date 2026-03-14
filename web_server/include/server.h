/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
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
