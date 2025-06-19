#include "auth.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// Dummy user/pass table
static const char* valid_user = "admin";
static const char* valid_pass = "password";

bool auth_check(const char* auth_header, const char* realm) {
    if (!auth_header) return false;
    if (strncmp(auth_header, "Basic ", 6) != 0) return false;
    // Decode base64
    char decoded[256];
    // (Implementation omitted for brevity)
    // Check user:pass matches
    if (strcmp(decoded, "admin:password") == 0)
        return true;
    return false;
}
void auth_send_challenge(int fd, const char* realm) {
    char buf[256];
    snprintf(buf, sizeof(buf),
        "HTTP/1.1 401 Unauthorized\r\nWWW-Authenticate: Basic realm=\"%s\"\r\n\r\n", realm);
    send(fd, buf, strlen(buf), 0);
}