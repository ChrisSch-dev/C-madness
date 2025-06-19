#include "scene.h"
#include "render.h"
#include "config.h"
#include "anim.h"
#include "image_io.h"
#include "distributed.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    scene_config_t conf;
    load_scene_config(argv[1], &conf);
    scene_t scene;
    scene_init(&scene, &conf);
    int frames = conf.frames;
    for (int frame = 0; frame < frames; frame++) {
        if (frames > 1) animate_scene(&scene, frame/(float)frames);
        // Distributed rendering or local
        #ifdef USE_DISTRIBUTED
        render_distributed(&scene, conf.width, conf.height, conf.samples, conf.outdir);
        #else
        unsigned char* img = malloc(conf.width*conf.height*3);
        render_scene(&scene, img, conf.width, conf.height, conf.samples);
        char fname[256];
        sprintf(fname, "%s/frame_%04d.png", conf.outdir, frame);
        write_png(fname, img, conf.width, conf.height);
        free(img);
        #endif
    }
    scene_free(&scene);
    return 0;
}