#pragma once
void logger_init(const char* filename);
void logger_log(const char* ip, const char* path, int status);
void logger_close();