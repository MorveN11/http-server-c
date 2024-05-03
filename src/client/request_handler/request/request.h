#include "request_type/request_type.h"

#ifndef REQUEST_H
#define REQUEST_H

#define MAX_BUFFER_SIZE 2048

struct Request {
    enum RequestType type;
    char *path;
    char *http_version;
    char *host;
    char *content_type;
    char *user_agent;
    char *accept;
    int content_length;
    char *body;
};

struct Request parse_request(char *request);

char *request_to_string(struct Request *request);

#endif
