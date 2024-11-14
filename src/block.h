#ifndef BLOCK_H
#define BLOCK_H

#include <cglm/cglm.h>

typedef struct {
    vec3 position;
    vec3 color;
    float size;
} block_t;

block_t block_create(vec3 position, float size, vec3 color);

#endif