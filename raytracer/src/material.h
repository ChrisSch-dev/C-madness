#pragma once
typedef struct {
    int type; // diffuse, metal, glass, etc.
    float color[3];
    float roughness;
    float ior;
    struct texture_t* tex;
} material_t;