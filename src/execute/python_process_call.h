#ifndef python_h
#define python_h

#define UNIQUE_ID_LENGTH 28
#define MILISECONDS_AMOUNT 8
#define TMP_FILENAME_LENGTH 38
#define COMMAND_LENGTH 50
#define CONTENT_SIZE 2048
#define BUFFER_SIZE 512
#define FILE_ERROR_NAME_SIZE 48
#define CWD_SIZE 1024

struct PythonOutput {
    char *output;
    int status;
};

struct PythonOutput *execute_python_code(const char *python_code);

#endif
