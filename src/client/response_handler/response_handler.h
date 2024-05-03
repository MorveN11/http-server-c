#include "../request_handler/request/request.h"
#include "../request_handler/request/request_type/request_type.h"

#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#define NOT_FOUND_RESPONSE "HTTP/1.1 404 NOT FOUND\r\n\r\n"
#define OK_RESPONSE "HTTP/1.1 200 OK\r\n\r\n"

struct HttpResponse {
    char *path;
    char *(*handler)(struct Request);
};

struct Routes {
    enum RequestType key;
    struct HttpResponse *responses;
};

int handle_response(int client_fd, struct Request request);

#endif
