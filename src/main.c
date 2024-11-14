#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "block_renderer.h"

void on_render();
void on_init();
void on_destroy();

GLFWwindow *window;
shader_t shader;

block_renderer_t *renderer;

int main(int argc, char **argv) {
    glfwInit();
    window = glfwCreateWindow(800, 600, "Thretris", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

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
}

void on_destroy() {
    block_renderer_free(renderer);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void on_render() {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_use(shader);
    block_renderer_draw(renderer);

    glfwPollEvents();
    glfwSwapBuffers(window);
}