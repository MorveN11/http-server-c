#include "connection.h"
#include <netinet/in.h>
#include <stdlib.h>

int handle_connection(int server_fd) {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);

    if (client_fd == -1) {
        return EXIT_FAILURE;
    }

    return client_fd;
}
