#include "client/client.h"
#include "connection/connection.h"
#include "routes/routes.h"
#include "server/server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    int server_fd = start_server();

    if (server_fd == -1) {
        printf("Server failed to start\n\n");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n\n", PORT);

    signal(SIGINT, &stop_server);

    struct Routes *routes = get_routes();

    while (1) {
        printf("Waiting for client connection...\n\n");

        int client_fd = handle_connection(server_fd);

        if (client_fd == -1) {
            printf("Failed to accept client connection\n");
            continue;
        }

        pid_t pid = fork();

        if (pid == -1) {
            printf("Failed to fork\n");
            close(client_fd);
            continue;
        }

        if (pid == 0) {
            close(server_fd);
            exit(handle_client(client_fd, routes));
        }

        close(client_fd);
        waitpid(-1, NULL, WNOHANG);
    }

    return EXIT_SUCCESS;
}
