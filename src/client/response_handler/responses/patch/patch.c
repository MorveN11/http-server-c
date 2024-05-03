#include "patch.h"
#include "../../response_handler.h"
#include <stdlib.h>

struct HttpResponse http_patch_responses[] = {NULL};

struct HttpResponse *get_patch_responses() { return http_patch_responses; }
