#include "render.h"
#include "vec.h"
#include <math.h>
#include <pthread.h>
typedef struct {
    scene_t* scene;
    unsigned char* img;
    int w, h, y0, y1;
} job_t;

float intersect_sphere(vec3 ro, vec3 rd, object_t* obj) {
    vec3 oc = vsub(ro, obj->pos);
    float b = 2*vdot(oc, rd);
    float c = vdot(oc,oc) - obj->radius*obj->radius;
    float d = b*b - 4*c;
    if (d<0) return -1;
    float s = sqrtf(d);
    float t0 = (-b-s)/2, t1=(-b+s)/2;
    return (t0>0.01f)?t0:(t1>0.01f?t1:-1);
}
float intersect_plane(vec3 ro, vec3 rd, object_t* obj) {
    float denom = vdot(obj->norm, rd);
    if (fabs(denom)<1e-6) return -1;
    float t = vdot(vsub(obj->pos, ro), obj->norm)/denom;
    return (t>0.01)?t:-1;
}
vec3 trace_ray(scene_t* s, vec3 ro, vec3 rd, int depth) {
    float tmin=1e9; object_t* hit=NULL;
    for (int i=0;i<s->nobjs;i++) {
        float t=-1;
        if (s->objs[i].type==OBJ_SPHERE)
            t = intersect_sphere(ro,rd,&s->objs[i]);
        else if (s->objs[i].type==OBJ_PLANE)
            t = intersect_plane(ro,rd,&s->objs[i]);
        if (t>0 && t<tmin) { tmin=t; hit=&s->objs[i]; }
    }
    if (!hit) return v3(0.2,0.2,0.2);
    vec3 phit = vadd(ro, vscale(rd, tmin));
    vec3 nhit = (hit->type==OBJ_SPHERE)?
        vnorm(vsub(phit,hit->pos)) : hit->norm;
    vec3 col = vscale(hit->color, 0.1f);
    for (int l=0;l<s->nlights;l++) {
        vec3 ldir = vnorm(vsub(s->lights[l].pos, phit));
        // Shadow
        int shadow=0;
        for (int j=0;j<s->nobjs;j++) if (&s->objs[j]!=hit) {
            float t=-1;
            if (s->objs[j].type==OBJ_SPHERE)
                t = intersect_sphere(phit, ldir, &s->objs[j]);
            else if (s->objs[j].type==OBJ_PLANE)
                t = intersect_plane(phit, ldir, &s->objs[j]);
            if (t>0.01 && t<vdot(vsub(s->lights[l].pos, phit), ldir)) shadow=1;
        }
        float diff = fmaxf(0, vdot(nhit, ldir));
        // Specular
        vec3 refl = vsub(vscale(nhit, 2*vdot(nhit,ldir)), ldir);
        float spec = powf(fmaxf(0, vdot(refl, vscale(rd,-1))), 16);
        if (!shadow) {
            col = vadd(col, vscale(hit->color, diff));
            col = vadd(col, vscale(s->lights[l].color, spec));
        }
    }
    // Reflection
    if (depth<2 && hit->reflect>0.05f) {
        vec3 rdir = vsub(rd, vscale(nhit, 2*vdot(rd,nhit)));
        vec3 rcol = trace_ray(s, vadd(phit, vscale(nhit,0.01)), vnorm(rdir), depth+1);
        col = vadd(col, vscale(rcol, hit->reflect));
    }
    col.x=fminf(col.x,1.0f); col.y=fminf(col.y,1.0f); col.z=fminf(col.z,1.0f);
    return col;
}
static void* worker(void* arg) {
    job_t* j = (job_t*)arg;
    for (int y=j->y0; y<j->y1; y++) for (int x=0; x<j->w; x++) {
        float fx = (2*(x+0.5)/j->w-1)*j->w/j->h;
        float fy = 1-2*(y+0.5)/j->h;
        vec3 ro = v3(0,0,0);
        vec3 rd = vnorm(v3(fx,fy,-1));
        vec3 col = trace_ray(j->scene, ro, rd, 0);
        int idx = (y*j->w+x)*3;
        j->img[idx+0]=255*col.x;
        j->img[idx+1]=255*col.y;
        j->img[idx+2]=255*col.z;
    }
    return NULL;
}
void render_scene(scene_t* scene, unsigned char* img, int w, int h, int nthreads) {
    pthread_t* tids = malloc(sizeof(pthread_t)*nthreads);
    job_t* jobs = malloc(sizeof(job_t)*nthreads);
    for (int t=0; t<nthreads; t++) {
        jobs[t]=(job_t){scene,img,w,h,h*t/nthreads,h*(t+1)/nthreads};
        pthread_create(&tids[t],NULL,worker,&jobs[t]);
    }
    for (int t=0;t<nthreads;t++)
        pthread_join(tids[t],NULL);
    free(tids); free(jobs);
}