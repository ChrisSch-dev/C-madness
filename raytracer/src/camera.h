#pragma once
typedef struct {
    float pos[3], target[3], up[3], fov, aspect, aperture, focus_dist;
} camera_t;
void camera_setup(camera_t* cam, const scene_config_t* conf);