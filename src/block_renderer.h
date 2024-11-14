#ifndef BLOCK_RENDERER_H
#define BLOCK_RENDERER_H

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdlib.h>

typedef struct {
    GLuint vb;
    GLuint eb;
    GLuint va;
} block_renderer_t;

block_renderer_t *block_renderer_create();
void block_renderer_free(block_renderer_t *renderer);

void block_renderer_draw(block_renderer_t *renderer);

#endif