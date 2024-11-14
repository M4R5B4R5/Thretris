#ifndef BLOCK_RENDERER_H
#define BLOCK_RENDERER_H

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdlib.h>

#include "block.h"
#include "shader.h"

typedef struct {
    GLuint vb;
    GLuint eb;
    GLuint wire_eb;
    GLuint va;
} block_renderer_t;

block_renderer_t *block_renderer_create();
void block_renderer_free(block_renderer_t *renderer);

void block_renderer_render_debug(block_renderer_t *renderer, block_t block, shader_t shader);

#endif