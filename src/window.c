#include "window.h"

float window_get_aspect(GLFWwindow *window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return (float)width / (float)height;
}