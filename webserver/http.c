#include "http.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <strings.h>

typedef struct mime_entry {
    char ext[16];
    char type[64];
    struct mime_entry* next;
} mime_entry_t;

static mime_entry_t* mime_types = NULL;

void mime_load_types(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return;
    char buf[128], ext[16], type[64];
    while (fgets(buf, sizeof(buf), f)) {
        if (sscanf(buf, "%s %s", ext, type) == 2) {
            mime_entry_t* e = malloc(sizeof(*e));
            strcpy(e->ext, ext);
            strcpy(e->type, type);
            e->next = mime_types;
            mime_types = e;
        }
    }
    fclose(f);
}
const char* mime_type(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!ext) return "application/octet-stream";
    ext++;
    for (mime_entry_t* e = mime_types; e; e = e->next) {
        if (!strcasecmp(ext, e->ext)) return e->type;
    }
    return "application/octet-stream";
}

static void send_header(int fd, int status, const char* type, long length) {
    char buf[512];
    snprintf(buf, sizeof(buf),
        "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n",
        status, (status==200)?"OK":(status==404)?"Not Found":"Error", type, length);
    send(fd, buf, strlen(buf), 0);
}

static void directory_listing(int fd, const char* path, const char* url) {
    DIR* dir = opendir(path);
    if (!dir) { send_header(fd, 403, "text/plain", 0); return; }
    char buf[4096];
    int len = snprintf(buf, sizeof(buf),
        "<html><body><h2>Index of %s</h2><ul>", url);
    struct dirent* ent;
    while ((ent = readdir(dir))) {
        len += snprintf(buf+len, sizeof(buf)-len, "<li><a href=\"%s%s%s\">%s</a></li>",
            url, url[strlen(url)-1]=='/'?"":"/", ent->d_name, ent->d_name);
    }
    len += snprintf(buf+len, sizeof(buf)-len, "</ul></body></html>");
    closedir(dir);
    send_header(fd, 200, "text/html", len);
    send(fd, buf, len, 0);
}

void http_handle_request(int client_fd, const char* root, const char* client_ip) {
    char buf[2048], method[16], url[1024];
    int recvd = recv(client_fd, buf, sizeof(buf)-1, 0);
    if (recvd <= 0) return;
    buf[recvd] = 0;
    sscanf(buf, "%15s %1023s", method, url);
    if (strcmp(method, "GET")) {
        send_header(client_fd, 405, "text/plain", 0);
        logger_log(client_ip, url, 405);
        return;
    }
    char path[2048];
    snprintf(path, sizeof(path), "%s%s", root, url);
    struct stat st;
    if (stat(path, &st) < 0) {
        send_header(client_fd, 404, "text/plain", 0);
        logger_log(client_ip, url, 404);
        return;
    }
    if (S_ISDIR(st.st_mode)) {
        // Directory index
        directory_listing(client_fd, path, url);
        logger_log(client_ip, url, 200);
        return;
    }
    FILE* f = fopen(path, "rb");
    if (!f) {
        send_header(client_fd, 403, "text/plain", 0);
        logger_log(client_ip, url, 403);
        return;
    }
    send_header(client_fd, 200, mime_type(path), st.st_size);
    while (!feof(f)) {
        size_t n = fread(buf, 1, sizeof(buf), f);
        if (n) send(client_fd, buf, n, 0);
    }
    fclose(f);
    logger_log(client_ip, url, 200);
}