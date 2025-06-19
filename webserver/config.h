#pragma once
#include <stdbool.h>
#define MAX_DOMAINS 16

typedef struct {
    char domain[128];
    int port;
    char root[256];
    char cert_file[256];
    char key_file[256];
} vhost_conf_t;

typedef struct {
    int listen_port;
    char listen_ip[64];
    char logfile[256];
    char error_page[256];
    int max_clients;
    char allow_ips[32][64];
    int n_allow;
    char deny_ips[32][64];
    int n_deny;
    vhost_conf_t vhosts[MAX_DOMAINS];
    int n_vhosts;
} server_conf_t;

extern server_conf_t server_conf;

bool config_load(const char* filename);