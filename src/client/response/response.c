#include "response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int handle_response(int client_fd) {
    int write_status = write(client_fd, OK_RESPONSE, strlen(OK_RESPONSE));

    if (write_status == -1) {
        return EXIT_FAILURE;
    }

    printf("Response Sent:\n\n");

    return EXIT_SUCCESS;
}
