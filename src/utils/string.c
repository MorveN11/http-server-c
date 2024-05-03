#include "string.h"
#include <stdlib.h>
#include <string.h>

char **split_string(char *str, char *delimiter) {
    char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
    char *token = strtok(str, delimiter);
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, delimiter);
    }
    tokens[i] = NULL;
    return tokens;
}

char *get_string_starts_with(char **list, char *start) {
    for (int i = 0; list[i] != NULL; i++) {
        if (strstr(list[i], start) != NULL) {
            return list[i];
        }
    }
    return NULL;
}

int get_string_list_size(char **list) {
    int size = 0;
    for (int i = 0; list[i] != NULL; i++) {
        size++;
    }
    return size;
}
