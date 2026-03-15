/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
#include "../include/server.h"

void handle_route(int socket, char *verb, char *route, char *payload) {

  if (strcmp(verb, "POST") == 0) {
    if (strcmp(route, "/assemble") == 0) {

      printf("POST /assemble\nPayload: %s\n", payload);

      char *separator =
          strstr(payload, "\r\n\r\n"); // Extract assembly code, starts in
                                       // payload after \r\n\r\n
      char *assembly_code = (separator != NULL) ? separator + 4 : "HALT\n";
      printf("Attempting to compile:\n'%s'\n", assembly_code);

      assemble_request(assembly_code, socket);
    }
    if (strcmp(route, "/emulate") == 0) {

      printf("POST /emulate\nPayload: %s\n", payload);

      // Content length from header needed as strlen will not work for number of
      // machine code bytes

      int content_length = 0;
      char *cl_header = strstr(payload, "Content-Length: ");
      if (cl_header != NULL) {
        // Extract the integer right after the header name
        sscanf(cl_header, "Content-Length: %d", &content_length);
      }
      char *separator = strstr(payload, "\r\n\r\n");
      char *machine_code =
          (separator != NULL) ? separator + 4 : "\0\0\0\0\0\0\1\2";
      printf("Attempting to emulate:\n'%s'\n", machine_code);
      emulate_request(machine_code, content_length, socket);
    }
  } else if (strcmp(verb, "OPTIONS") == 0) {
    char *options_response =
        "HTTP/1.1 204 No Content\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type, Accept\r\n"
        "\r\n";

    write(socket, options_response, strlen(options_response));
    close(socket);
  }
}
