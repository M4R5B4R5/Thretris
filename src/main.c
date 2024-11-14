#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "block_renderer.h"
#include "camera.h"
#include "window.h"

void on_render();
void on_init();
void on_destroy();
void on_resize();

GLFWwindow *window;
shader_t shader;
camera_t camera;

block_renderer_t *renderer;

block_t block;

void on_resize(GLFWwindow *window, int width, int height) {
    camera_updateProjectionMatrix(&camera, window_get_aspect(window));
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);

        GLint mode = GL_LINE;
        if (polygonMode[0] == mode && polygonMode[1] == mode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, mode);
        }
    }
}

int main(int argc, char **argv) {
    glfwInit();
    window = glfwCreateWindow(800, 600, "Thretris", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, on_resize);
    glfwSetKeyCallback(window, key_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    on_init();
    while (!glfwWindowShouldClose(window)) {
        on_render();
    }
    on_destroy();

    return 0;
}

void on_init() {
    renderer = block_renderer_create();
    shader = shader_create("src/glsl/shader.vert", "src/glsl/shader.frag");
    shader_use(shader);

    camera = camera_create((vec3) {3.0f, 0.0f, 3.0f}, shader);
    camera_setGaze(&camera, (vec3) {0.0f, 0.0f, 0.0f});
    camera_updateProjectionMatrix(&camera, window_get_aspect(window));

    block = block_create((vec3) {0.0f, 0.0f, 0.0f}, 1.0f, (vec3) {0.0f, 0.0f, 0.0f});
}

void on_destroy() {
    block_renderer_free(renderer);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void on_render() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm_vec3_rotate(camera.position, 0.01f, (vec3) {0.0f, 1.0f, 0.0f});
    camera_setGaze(&camera, block.position);
    camera_updateViewMatrix(&camera);    

    block_renderer_render_debug(renderer, block, shader);

    glfwPollEvents();
    glfwSwapBuffers(window);
}