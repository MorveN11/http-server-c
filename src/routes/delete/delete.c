#include "delete.h"
#include "../routes.h"
#include <stdlib.h>

struct Response http_delete_responses[] = {NULL};

struct Response *get_delete_responses() { return http_delete_responses; }
