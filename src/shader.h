#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct {
    GLuint id;
} shader_t;

shader_t shader_create(const char *vertex_path, const char *fragment_path);

void shader_use(shader_t shader);
void shader_destroy(shader_t shader);

void shader_set_mat4fv(shader_t shader, mat4 matrix, const char *name);
void shader_set_int(shader_t shader, const char *name, vec3 v3);

#endif