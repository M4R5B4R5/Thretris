#include "camera.h"

camera_t camera_create(vec3 position, shader_t shader) {
    camera_t camera;
    camera.shader = shader;
    glm_vec3_copy(position, camera.position);
    glm_vec3_copy((vec3) {0.0f, 0.0f, 1.0f}, camera.gaze);

    return camera;
}

void camera_setGaze(camera_t *camera, vec3 target) {
    glm_vec3_sub(camera->position, target, camera->gaze);
    glm_vec3_normalize(camera->gaze);
}

void camera_updateViewMatrix(camera_t *camera) {
    vec3 eye;
    glm_vec3_add(camera->position, camera->gaze, eye);

    glm_lookat(eye, camera->position, (vec3) {0.0f, 1.0f, 0.0f}, camera->view);

    shader_use(camera->shader);
    shader_set_mat4fv(camera->shader, camera->view, "view");
}

void camera_updateProjectionMatrix(camera_t *camera, float aspect) {
    glm_perspective(45.0f, aspect, 0.1f, 100.0f, camera->projection);
    shader_use(camera->shader);
    shader_set_mat4fv(camera->shader, camera->projection, "projection");
}