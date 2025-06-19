#pragma once
int add_area_light(scene_t* scene, float pos[3], float normal[3], float size[2], float color[3]);
float sample_area_light(const area_light_t* light, float* pos, float* normal);