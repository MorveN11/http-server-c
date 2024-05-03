#include "put.h"
#include "../../response_handler.h"
#include <stdlib.h>

struct HttpResponse http_put_responses[] = {NULL};

struct HttpResponse *get_put_responses() { return http_put_responses; }
