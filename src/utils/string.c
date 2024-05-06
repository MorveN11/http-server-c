#include "string.h"
#include <stdio.h>
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

char *get_substring(char *str, int start) {
    int size = strlen(str) - start + 1;
    char *substring = (char *)malloc(size * sizeof(char));

    if (substring == NULL) {
        printf("Failed to allocate memory for substring\n");
        return NULL;
    }

    for (int i = start, j = 0; str[i] != '\0'; i++, j++) {
        substring[j] = str[i];
    }

    substring[size - 1] = '\0';

    return substring;
}

int get_index_string_starts_with(char **list, char *start) {
    for (int i = 0; list[i] != NULL; i++) {
        if (strstr(list[i], start) != NULL) {
            return i;
        }
    }

    return -1;
}

int get_string_list_size(char **list) {
    int size = 0;
    for (int i = 0; list[i] != NULL; i++) {
        size++;
    }
    return size;
}
