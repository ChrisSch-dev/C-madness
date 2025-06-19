#pragma once
typedef struct { float x, y, z; } vec3;
vec3 v3(float x, float y, float z);
vec3 vadd(vec3 a, vec3 b);
vec3 vsub(vec3 a, vec3 b);
vec3 vscale(vec3 a, float s);
float vdot(vec3 a, vec3 b);
float vlen(vec3 a);
vec3 vnorm(vec3 a);