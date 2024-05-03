#include "delete.h"
#include "../../response_handler.h"
#include <stdlib.h>

struct HttpResponse http_delete_responses[] = {NULL};

struct HttpResponse *get_delete_responses() { return http_delete_responses; }
