#include "get.h"
#include "../../client/request_handler/request/request.h"
#include "../routes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *handle_root(struct Request *request) {
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 111\r\n\r\nHttp Server built with "
                     "C\nVersion 1.0\nView on GitHub: https://github.com/MorveN11/http-server-c\nAuthor: MorveN11";
    return response;
}

char *handle_get_file(struct Request *request) {
    char actual_path[PATH_SIZE];

    if (getcwd(actual_path, sizeof(actual_path)) == NULL) {
        return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nContent-Length: 39\r\n\r\nFailed to "
               "get current working directory";
    }

    char *sub_path = request->path;
    char *file_path = (char *)malloc(strlen(actual_path) + strlen(sub_path) + 1);

    if (file_path == NULL) {
        return "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nContent-Length: 39\r\n\r\nFailed to "
               "allocate memory for file path";
    }

    strcpy(file_path, actual_path);
    strcat(file_path, sub_path);

    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 14\r\n\r\nFile not found";
    }

    char line[LINE_SIZE];
    char content[CONTENT_SIZE] = {0};

    while (fgets(line, sizeof(line), file) != NULL) {
        strcat(content, line);
    }

    char content_type[CONTENT_TYPE_SIZE] = "text/";
    char *dot = strrchr(file_path, '.');

    if (!dot || dot == file_path) {
        strcat(content_type, "plain");
    } else {
        if (strcmp(dot, ".html") == 0) {
            strcat(content_type, "html");
        } else if (strcmp(dot, ".css") == 0) {
            strcat(content_type, "css");
        } else if (strcmp(dot, ".js") == 0) {
            strcat(content_type, "javascript");
        } else {
            strcat(content_type, "plain");
        }
    }

    int response_size = strlen("HTTP/1.1 200 OK\r\nContent-Type: ") + strlen(content_type) +
                        strlen("\r\nContent-Length: ") + snprintf(NULL, 0, "%zu", strlen(content)) + 4 +
                        strlen(content) + 1;

    char *response = (char *)malloc(response_size * sizeof(char));

    snprintf(response, response_size, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n%s",
             content_type, strlen(content), content);

    return response;
}

struct Response http_get_responses[] = {
    {"/", handle_root, 0},
    {"/", handle_get_file, 1},
    NULL,
};

struct Response *get_get_responses() { return http_get_responses; }
