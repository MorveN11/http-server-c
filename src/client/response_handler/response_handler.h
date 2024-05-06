#include "../../routes/routes.h"
#include "../request_handler/request/request.h"

#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#define NOT_FOUND_RESPONSE                                                                                             \
    "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nRoute Not Found"

int handle_response(int client_fd, struct Request *request, struct Routes *routes);

#endif
