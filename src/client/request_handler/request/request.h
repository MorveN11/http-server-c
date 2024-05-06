#include "request_type/request_type.h"

#ifndef REQUEST_H
#define REQUEST_H

#define MAX_BUFFER_SIZE 2048
#define METHOD_SIZE 8
#define PATH_SIZE 1024
#define HTTP_VERSION_SIZE 16
#define HOST_SIZE 128
#define CONTENT_TYPE_SIZE 128
#define USER_AGENT_SIZE 128
#define ACCEPT_SIZE 128
#define CONTENT_LENGTH_SIZE 128

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
