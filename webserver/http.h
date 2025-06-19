#pragma once
void http_handle_request(int client_fd, const char* root, const char* client_ip);
void mime_load_types(const char* filename);
const char* mime_type(const char* filename);