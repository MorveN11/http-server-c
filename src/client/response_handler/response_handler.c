#include "response_handler.h"
#include "../request_handler/request/request.h"
#include "responses/delete/delete.h"
#include "responses/get/get.h"
#include "responses/patch/patch.h"
#include "responses/post/post.h"
#include "responses/put/put.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct HttpResponse *get_response_by_path(struct HttpResponse *responses, char *path) {

    if (responses == NULL) {
        return NULL;
    }

    for (int i = 0; responses[i].path != NULL; i++) {
        if (strcmp(responses[i].path, path) == 0) {
            return &responses[i];
        }
    }

    return NULL;
}

int handle_response(int client_fd, struct Request request) {
    struct Routes routes[] = {
        {GET, (struct HttpResponse *)get_get_responses()},     {POST, (struct HttpResponse *)get_post_responses()},
        {PUT, (struct HttpResponse *)get_put_responses()},     {DELETE, (struct HttpResponse *)get_delete_responses()},
        {PATCH, (struct HttpResponse *)get_patch_responses()}, {UNKNOWN, (struct HttpResponse *){NULL}},
    };

    char *response_message;

    struct HttpResponse *responses = routes[request.type].responses;

    struct HttpResponse *response = get_response_by_path(responses, request.path);

    if (response == NULL) {
        response_message = NOT_FOUND_RESPONSE;
    } else {
        response_message = response->handler(request);
    }

    int write_status = write(client_fd, response_message, strlen(response_message));

    if (write_status == -1) {
        return EXIT_FAILURE;
    }

    printf("Response Sent:\n%s", response_message);

    return EXIT_SUCCESS;
}
