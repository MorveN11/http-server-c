#include "post.h"
#include "../../execute/python.h"
#include "../routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *handle_execute_py(struct Request *request) {
    char extension[EXTENSION_SIZE] = {0};
    char *dot = strrchr(request->path, '.');

    if (!dot || dot == request->path) {
        return "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\r\nContent-Length: 22\r\n\r\nOnly .py files allowed";
    } else {
        if (strcmp(dot, ".py") != 0) {
            return "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\r\nContent-Length: 22\r\n\r\nOnly .py files "
                   "allowed";
        }
        strcpy(extension, dot + 1);
    }

    char *body = request->body;
    char *output = execute_python_code(body);

    if (output == NULL) {
        return "HTTP/1.1 500 Internal Server Error\nContent-Type: text/plain\r\nContent-Length: 27\r\n\r\nError "
               "executing "
               "Python code";
    }

    int response_size = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: ") +
                        snprintf(NULL, 0, "%zu", strlen(output)) + 4 + strlen(output) + 1;

    char *response = (char *)malloc(response_size * sizeof(char));

    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s",
             strlen(output), output);

    return response;
}

struct Response http_post_responses[] = {{"/", handle_execute_py, 1}, NULL};

struct Response *get_post_responses() { return http_post_responses; }
