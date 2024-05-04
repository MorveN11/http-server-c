#include "request.h"
#include "../../../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_request_attribute_by_key(char **request, char *key) {
    char *value = "";
    char *value_line = get_string_starts_with(request, key);

    if (value_line != NULL) {
        value = split_string(value_line, " ")[1];
    }

    return value;
}

struct Request parse_request(char *request) {
    char **tokens = split_string(request, "\r\n");

    char **request_line = split_string(tokens[0], " ");

    char *host = get_request_attribute_by_key(tokens, "Host");

    char *content_type = get_request_attribute_by_key(tokens, "Content-Type");

    char *user_agent = get_request_attribute_by_key(tokens, "User-Agent");

    char *accept = get_request_attribute_by_key(tokens, "Accept");

    int content_length = 0;
    char *content_length_string = get_request_attribute_by_key(tokens, "Content-Length");

    if (strcmp(content_length_string, "") != 0) {
        content_length = atoi(content_length_string);
    }

    char *body = "[No Body Recieved]";

    if (content_length > 0) {
        body = tokens[get_string_list_size(tokens) - 1];
    }

    return (struct Request){
        .type = parse_request_type(request_line[0]),
        .path = request_line[1],
        .http_version = request_line[2],
        .host = host,
        .content_type = content_type,
        .user_agent = user_agent,
        .accept = accept,
        .content_length = content_length,
        .body = body,
    };
}

char *request_to_string(struct Request *request) {
    char *request_string = malloc(sizeof(char) * MAX_BUFFER_SIZE);

    sprintf(request_string,
            "%s %s %s\r\nHost: %s\r\nContent-Type: %s\r\nUser-Agent: %s\r\nAccept: %s\r\nContent-Length: %d\r\n\r\n%s",
            request_type_to_string(request->type), request->path, request->http_version, request->host,
            request->content_type, request->user_agent, request->accept, request->content_length, request->body);

    return request_string;
}
