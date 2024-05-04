#include "get.h"
#include "../../client/request_handler/request/request.h"
#include "../../utils/string.h"
#include "../routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_root(struct Request *request) { return "HTTP/1.1 200 OK\r\n\r\n"; }

char *handle_echo(struct Request *request) {
    char *sub_path = get_substring(request->path, 6);

    int response_size = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: ") +
                        snprintf(NULL, 0, "%zu", strlen(sub_path)) + 4 + strlen(sub_path) + 1;
    char *response = (char *)malloc(response_size * sizeof(char));

    if (response == NULL) {
        printf("Error allocating memory for response\n");
        return NULL;
    }

    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s",
             strlen(sub_path), sub_path);

    return response;
}

char *handle_user_agent(struct Request *request) {
    int response_size = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: ") +
                        snprintf(NULL, 0, "%zu", strlen(request->user_agent)) + 4 + strlen(request->user_agent) + 1;
    char *response = (char *)malloc(response_size * sizeof(char));

    if (response == NULL) {
        printf("Error allocating memory for response\n");
        return NULL;
    }

    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s",
             strlen(request->user_agent), request->user_agent);

    return response;
}

struct Response http_get_responses[] = {
    {"/", handle_root, 0},
    {"/echo/", handle_echo, 1},
    {"/user-agent", handle_user_agent, 0},
    NULL,
};

struct Response *get_get_responses() { return http_get_responses; }
