#pragma once
#include "material.h"
int load_texture(const char* filename, texture_t* tex);
void sample_texture(const texture_t* tex, float u, float v, float* rgb);