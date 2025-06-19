#pragma once
void bvh_build(scene_t* scene);
int bvh_intersect(const scene_t* scene, const ray_t* ray, hit_t* hit);