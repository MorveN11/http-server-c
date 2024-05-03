#include "server.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int server_fd;

void stop_server() {
    printf("Stopping server...\n");
    close(server_fd);

    exit(EXIT_SUCCESS);
}

int start_server() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        printf("Socket creation failed: %s...\n", strerror(errno));
        return EXIT_FAILURE;
    }

    int reuse = 1;
    int set_socket_status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    if (set_socket_status < 0) {
        printf("SO_REUSEPORT failed: %s \n", strerror(errno));
        close(server_fd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr = {htonl(INADDR_ANY)},
    };
    int bind_status = bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (bind_status != 0) {
        printf("Bind failed: %s \n", strerror(errno));
        close(server_fd);
        return EXIT_FAILURE;
    }

    int listen_status = listen(server_fd, MAX_CONNECTIONS);

    if (listen_status != 0) {
        printf("Listen failed: %s \n", strerror(errno));
        close(server_fd);
        return EXIT_FAILURE;
    }

    return server_fd;
}
