#include "../../routes/routes.h"
#include "../request_handler/request/request.h"

#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#define NOT_FOUND_RESPONSE "HTTP/1.1 404 NOT FOUND\r\n\r\n"

int handle_response(int client_fd, struct Request *request, struct Routes *routes);

#endif
