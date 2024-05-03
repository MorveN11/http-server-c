#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int handle_request(int client_fd) {
    char buffer[MAX_BUFFER_SIZE] = {0};

    int read_status = read(client_fd, buffer, sizeof(buffer));

    if (read_status == -1) {
        return EXIT_FAILURE;
    }

    printf("\nRequest Recieved:\n%s", buffer);

    return EXIT_SUCCESS;
}
