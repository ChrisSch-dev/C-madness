#include "vec.h"
#include <math.h>
vec3 v3(float x, float y, float z) { vec3 v={x,y,z}; return v;}
vec3 vadd(vec3 a, vec3 b) {return v3(a.x+b.x,a.y+b.y,a.z+b.z);}
vec3 vsub(vec3 a, vec3 b) {return v3(a.x-b.x,a.y-b.y,a.z-b.z);}
vec3 vscale(vec3 a, float s) {return v3(a.x*s,a.y*s,a.z*s);}
float vdot(vec3 a, vec3 b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
float vlen(vec3 a) {return sqrt(vdot(a,a));}
vec3 vnorm(vec3 a) {return vscale(a,1.0f/vlen(a));}