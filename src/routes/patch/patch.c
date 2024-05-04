#include "patch.h"
#include "../routes.h"
#include <stdlib.h>

struct Response http_patch_responses[] = {NULL};

struct Response *get_patch_responses() { return http_patch_responses; }
