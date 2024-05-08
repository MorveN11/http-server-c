#include "python_process_call.h"
#include "../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *generate_unique_id() {
    char *unique_id = malloc(UNIQUE_ID_LENGTH);

    if (unique_id == NULL) {
        printf("Unique ID memory allocation failed\n");
        return NULL;
    }

    time_t current_time;
    struct tm *time_info;
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    time(&current_time);
    time_info = localtime(&current_time);

    strftime(unique_id, UNIQUE_ID_LENGTH, "%Y-%m-%d-%H-%M-%S-", time_info);
    sprintf(unique_id + (UNIQUE_ID_LENGTH - MILISECONDS_AMOUNT), "%08ld", spec.tv_nsec / 10);

    return unique_id;
}

struct PythonOutput *execute_python_code(const char *python_code) {
    char tmp_filename[TMP_FILENAME_LENGTH];
    char *unique_id = generate_unique_id();

    if (unique_id == NULL) {
        return NULL;
    }

    snprintf(tmp_filename, sizeof(tmp_filename), "temp_%s.py", unique_id);

    FILE *tmp_file = fopen(tmp_filename, "w");

    if (tmp_file == NULL) {
        printf("Error creating temp file\n");

        free(unique_id);

        return NULL;
    }

    fprintf(tmp_file, "%s", python_code);
    fclose(tmp_file);

    char command[COMMAND_LENGTH];
    snprintf(command, sizeof(command), "python3 %s 2>&1", tmp_filename);

    FILE *python_pipe = popen(command, "r");

    if (python_pipe == NULL) {
        printf("Error executing command\n");

        remove(tmp_filename);
        free(unique_id);

        return NULL;
    }

    struct PythonOutput *execution = (struct PythonOutput *)malloc(sizeof(struct PythonOutput));

    char buffer[BUFFER_SIZE];
    char output[CONTENT_SIZE] = {0};
    int status = 0;
    char cwd[CWD_SIZE];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current working directory\n");

        pclose(python_pipe);
        remove(tmp_filename);
        free(unique_id);

        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), python_pipe) != NULL) {
        if (strstr(buffer, "  File") != NULL) {
            char *substring = get_substring(buffer, FILE_ERROR_NAME_SIZE + strlen(cwd));
            strcpy(buffer, substring);

            status = 1;
        }
        strcat(output, buffer);
    }

    pclose(python_pipe);
    remove(tmp_filename);
    free(unique_id);

    execution->status = status;
    execution->output = output;

    return execution;
};
