#include "post.h"
#include "../routes.h"
#include <stdlib.h>

struct Response http_post_responses[] = {NULL};

struct Response *get_post_responses() { return http_post_responses; }
