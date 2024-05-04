#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#define MAX_TOKENS 100

char **split_string(char *str, char *delimiter);

char *get_string_starts_with(char **list, char *start);

char *get_substring(char *str, int start);

int get_string_list_size(char **list);

#endif
