#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <stdlib.h>

#include "shader.h"

typedef struct {
    shader_t shader;
    vec3 position;
    vec3 gaze;
    mat4 view;
    mat4 projection;
} camera_t;

camera_t camera_create(vec3 position, shader_t shader);

void camera_setGaze(camera_t *camera, vec3 target);
void camera_updateViewMatrix(camera_t *camera);
void camera_updateProjectionMatrix(camera_t *camera, float aspect);

#endif