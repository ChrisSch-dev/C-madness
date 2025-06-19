#include "scene.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main() {
    scene_t scene;
    scene_init(&scene);
    unsigned char* img = malloc(WIDTH*HEIGHT*3);
    render_scene(&scene, img, WIDTH, HEIGHT, 4); // 4 threads
    printf("P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(img, 1, WIDTH*HEIGHT*3, stdout);
    free(img);
    scene_free(&scene);
    return 0;
}