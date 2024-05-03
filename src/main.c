#include "client/client.h"
#include "server/server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    int server_fd = start_server();

    if (server_fd == -1) {
        printf("Server failed to start\n\n");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n\n", PORT);

    signal(SIGINT, &stop_server);

    while (1) {
        printf("Waiting for client connection...\n\n");

        handle_client(server_fd);
    }

    return EXIT_SUCCESS;
}
