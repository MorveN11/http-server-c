#include "request_handler.h"
#include "request/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Request *handle_request(int client_fd) {
    char buffer[MAX_BUFFER_SIZE] = {0};

    int read_status = read(client_fd, buffer, sizeof(buffer));

    if (read_status == -1) {
        printf("Failed to read request\n");
        return NULL;
    }

    struct Request *request = (struct Request *)malloc(sizeof(struct Request));

    if (request == NULL) {
        printf("Failed to allocate memory for request\n");
        return NULL;
    }

    *request = parse_request(buffer);

    printf("\nRequest Recieved:\n%s\n\n", request_to_string(request));

    return request;
}
