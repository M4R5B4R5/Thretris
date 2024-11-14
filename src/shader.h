#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    GLuint id;
} shader_t;

shader_t shader_create(const char *vertex_path, const char *fragment_path);

void shader_use(shader_t shader);
void shader_destroy(shader_t shader);

#endif