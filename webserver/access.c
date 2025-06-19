#include "access.h"
#include "config.h"
#include <string.h>
bool access_allowed(const char* ip) {
    for (int i = 0; i < server_conf.n_deny; ++i)
        if (strcmp(ip, server_conf.deny_ips[i]) == 0) return false;
    if (server_conf.n_allow == 0) return true;
    for (int i = 0; i < server_conf.n_allow; ++i)
        if (strcmp(ip, server_conf.allow_ips[i]) == 0) return true;
    return false;
}