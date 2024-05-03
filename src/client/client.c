#include "client.h"
#include "connection/connection.h"
#include "request/request.h"
#include "response/response.h"
#include <stdio.h>

void handle_client(int server_fd) {
    int client_fd = handle_connection(server_fd);

    if (client_fd == -1) {
        printf("Failed to accept client connection\n");
        return;
    }

    printf("Client connected\n");

    int request_status = handle_request(client_fd);

    if (request_status == -1) {
        printf("Failed to read request\n");
        close_connection();
        return;
    }

    int response_status = handle_response(client_fd);

    if (response_status == -1) {
        printf("Failed to send response\n");
        close_connection();
        return;
    }

    close_connection();
    printf("Client disconnected\n\n");
}
