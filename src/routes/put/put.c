#include "put.h"
#include "../routes.h"
#include <stdlib.h>

struct Response http_put_responses[] = {NULL};

struct Response *get_put_responses() { return http_put_responses; }
