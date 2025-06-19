#pragma once
#include "vec.h"
typedef enum {OBJ_SPHERE, OBJ_PLANE} objtype_t;
typedef struct {
    objtype_t type;
    vec3 pos, norm, color;
    float radius;
    float reflect;
} object_t;
typedef struct {
    vec3 pos, color;
} light_t;
typedef struct {
    object_t* objs;
    int nobjs;
    light_t* lights;
    int nlights;
} scene_t;
void scene_init(scene_t* s);
void scene_free(scene_t* s);