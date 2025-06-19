#include "vhost.h"
#include "config.h"
#include <string.h>
const char* vhost_root_for(const char* host) {
    for (int i = 0; i < server_conf.n_vhosts; ++i)
        if (strcmp(server_conf.vhosts[i].domain, host) == 0)
            return server_conf.vhosts[i].root;
    return NULL;
}