#ifndef RESPONSE_H
#define RESPONSE_H

#define OK_RESPONSE "HTTP/1.1 200 OK\r\n\r\n"

int handle_response(int client_fd);

#endif
