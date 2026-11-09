//
// Created by aaa on 09/11/2026.
//

#include "donut.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TORUS_DIST 10.0f
#define R1 1.0f
#define R2 2.0f
#define REF_DIST 5.0f
#define K (RESX * 0.4f * REF_DIST / (R1 + R2))
#define SCREEN_DIST 0.1f

typedef struct fvec3{
    float x,y,z;
}fvec3;

extern char donut_frames[NUM_BYTES][RESX * RESY];
extern const float step;
extern const float TWO_PI;
const fvec3 light = { 0.0f, 0.7071f, -0.7071f};

float zbuffer[RESX * RESY];

static fvec3 rot_x(fvec3 v, float a) {
    float c = cosf(a), s = sinf(a);
    return (fvec3){ v.x, v.y * c - v.z * s, v.y * s + v.z * c };
}

static fvec3 rot_y(fvec3 v, float a) {
    float c = cosf(a), s = sinf(a);
    return (fvec3){ v.x * c + v.z * s, v.y, -v.x * s + v.z * c };
}

static fvec3 rot_z(fvec3 v, float a) {
    float c = cosf(a), s = sinf(a);
    return (fvec3) { v.x * c - v.y * s, v.x * s + v.y * c, v.z };
}

void init_donut_frames() {
    static const char shades[] = ".,-~:;=!*#$@";

    for (int i = 0; i < 256; ++i) {
        float A = i * step;
        float B = i * step * 2.0f;

        memset(zbuffer, 0, sizeof(float) * RESX * RESY);
        memset(donut_frames[i], ' ', RESX * RESY);

        for (float theta = 0; theta < TWO_PI; theta += 0.02f) {
            for (float phi = 0; phi < TWO_PI; phi += 0.02f) {

                fvec3 p = { R2 + R1 * cosf(theta), R1 * sinf(theta), 0.0f };
                fvec3 n = {cosf(theta), sinf(theta), 0.0f};

                p = rot_z(rot_x(rot_y(p, phi), A), B);
                n = rot_z(rot_x(rot_y(n, phi), A), B);

                p.z += TORUS_DIST;

                float inv_z = 1.0f / p.z;
                int x = (int)(RESX / 2 + K * p.x * inv_z);
                int y = (int)(RESY / 2 - K * p.y * inv_z);

                if (x < 0 || x >= RESX || y < 0 || y >= RESY) continue;
                if (inv_z <= zbuffer[x * RESY + y]) continue;
                zbuffer[x * RESY + y] = inv_z;

                float L = n.x * light.x + n.y * light.y + n.z * light.z;
                int idx = L > 0 ? (int)(L * 11.99f) : 0;
                donut_frames[i][x * RESY + y] = shades[idx];
            }
        }
    }
}
