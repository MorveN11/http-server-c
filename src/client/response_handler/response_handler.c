#include "response_handler.h"
#include "../../routes/routes.h"
#include "../request_handler/request/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Response *get_response_by_path(struct Response *responses, char *path) {
    if (responses == NULL) {
        return NULL;
    }

    for (int i = 0; responses[i].path != NULL; i++) {
        if (responses[i].starts_with == 0 && strcmp(responses[i].path, path) == 0) {
            return &responses[i];
        }

        if (responses[i].starts_with == 1 && strncmp(responses[i].path, path, strlen(responses[i].path)) == 0) {
            return &responses[i];
        }
    }

    return NULL;
}

int handle_response(int client_fd, struct Request *request, struct Routes *routes) {
    char *response_message;

    struct Response *responses = routes[request->type].responses;

    struct Response *response = get_response_by_path(responses, request->path);

    if (response == NULL) {
        response_message = NOT_FOUND_RESPONSE;
    } else {
        response_message = response->handler(request);
    }

    int write_status = write(client_fd, response_message, strlen(response_message));

    if (write_status == -1) {
        return EXIT_FAILURE;
    }

    int size = strlen(response_message);

    if (response_message[size - 1] == '\n') {
        printf("Response Sent:\n%s", response_message);
    } else {
        printf("Response Sent:\n%s\n\n", response_message);
    }

    return EXIT_SUCCESS;
}
