#include "scene.h"
#include <stdlib.h>

void scene_init(scene_t* s) {
    s->nobjs=3; s->objs=malloc(sizeof(object_t)*s->nobjs);
    s->objs[0] = (object_t){OBJ_SPHERE, {0,0,-5}, {0,0,0}, {1,0,0}, 1, 0.7};
    s->objs[1] = (object_t){OBJ_SPHERE, {2,0,-6}, {0,0,0}, {0,1,0}, 1, 0.2};
    s->objs[2] = (object_t){OBJ_PLANE, {0,-1,0}, {0,1,0}, {1,1,1}, 0, 0.1};
    s->nlights=1; s->lights=malloc(sizeof(light_t)*s->nlights);
    s->lights[0] = (light_t){{5,5,-2},{1,1,1}};
}
void scene_free(scene_t* s) {
    free(s->objs); free(s->lights);
}