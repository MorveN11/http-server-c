#include "../client/request_handler/request/request_type/request_type.h"
#include "delete/delete.h"
#include "get/get.h"
#include "patch/patch.h"
#include "post/post.h"
#include "put/put.h"
#include <stdio.h>
#include <stdlib.h>

struct Routes *get_routes() {
    struct Routes *routes = (struct Routes *)malloc(sizeof(struct Routes) * NUM_ROUTES);

    if (routes == NULL) {
        printf("Failed to allocate memory for routes\n");
        return NULL;
    }

    routes[0].key = GET;
    routes[0].responses = (struct Response *)get_get_responses();
    routes[1].key = POST;
    routes[1].responses = (struct Response *)get_post_responses();
    routes[2].key = PUT;
    routes[2].responses = (struct Response *)get_put_responses();
    routes[3].key = DELETE;
    routes[3].responses = (struct Response *)get_delete_responses();
    routes[4].key = PATCH;
    routes[4].responses = (struct Response *)get_patch_responses();
    routes[5].key = UNKNOWN;
    routes[5].responses = NULL;

    return routes;
}
