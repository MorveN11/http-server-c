#include "client.h"
#include "connection/connection.h"
#include "request_handler/request/request.h"
#include "request_handler/request_handler.h"
#include "response_handler/response_handler.h"
#include <stdio.h>

void handle_client(int server_fd) {
    int client_fd = handle_connection(server_fd);

    if (client_fd == -1) {
        printf("Failed to accept client connection\n");
        return;
    }

    printf("Client connected\n");

    struct Request *request = handle_request(client_fd);

    if (request == NULL) {
        printf("Failed to handle request\n");
        close_connection();
        return;
    }

    int response_status = handle_response(client_fd, *request);

    if (response_status == -1) {
        printf("Failed to send response\n");
        close_connection();
        return;
    }

    close_connection();

    printf("Client disconnected\n\n");
}
