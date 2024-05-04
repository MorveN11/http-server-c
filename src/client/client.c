#include "client.h"
#include "request_handler/request/request.h"
#include "request_handler/request_handler.h"
#include "response_handler/response_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int handle_client(int client_fd, struct Routes *routes) {

    printf("----- Client connected -----\n");

    struct Request *request = handle_request(client_fd);

    if (request == NULL) {
        printf("Failed to handle request\n");
        close(client_fd);
        return EXIT_FAILURE;
    }

    int response_status = handle_response(client_fd, request, routes);

    if (response_status == -1) {
        printf("Failed to send response\n");
        close(client_fd);
        return EXIT_FAILURE;
    }

    close(client_fd);

    printf("----- Client disconnected -----\n\n");

    return EXIT_SUCCESS;
}
