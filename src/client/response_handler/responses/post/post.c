#include "post.h"
#include "../../response_handler.h"
#include <stdlib.h>

struct HttpResponse http_post_responses[] = {NULL};

struct HttpResponse *get_post_responses() { return http_post_responses; }
