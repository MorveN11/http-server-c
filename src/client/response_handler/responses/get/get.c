#include "get.h"
#include "../../response_handler.h"
#include <stdlib.h>

char *handle_root(struct Request request) { return OK_RESPONSE; }

struct HttpResponse http_get_responses[] = {
    {"/", handle_root},
    NULL,
};

struct HttpResponse *get_get_responses() { return http_get_responses; }
