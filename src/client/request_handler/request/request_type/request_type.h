#ifndef REQUEST_TYPE_H
#define REQUEST_TYPE_H

enum RequestType {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    UNKNOWN,
};

enum RequestType parse_request_type(char *request_type);

char *request_type_to_string(enum RequestType request_type);

#endif
