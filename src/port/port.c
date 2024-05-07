#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int handle_port(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Error: Invalid number of arguments.\n");
        printf("Usage: ./server -p <port>\n\n");

        return -1;
    }

    if (strcmp(argv[1], "-p") != 0) {
        printf("Errro: The first argument must be -p.\n");

        return -1;
    }

    int port = atoi(argv[2]);

    for (int i = 0; i < strlen(argv[2]); i++) {
        if (!isdigit(argv[2][i])) {
            printf("Error: Port number must be a number.\n");

            return -1;
        }
    }

    if (port <= 0 || port > 65535) {
        printf("Error: Invalid port number.\n");

        return -1;
    }

    return port;
}
