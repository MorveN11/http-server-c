#include "../client/request_handler/request/request.h"
#include "../client/request_handler/request/request_type/request_type.h"

#ifndef ROUTES_H
#define ROUTES_H

#define NUM_ROUTES 6

struct Response {
    char *path;
    char *(*handler)(struct Request *);
    int starts_with;
};

struct Routes {
    enum RequestType key;
    struct Response *responses;
};

struct Routes *get_routes();

#endif
