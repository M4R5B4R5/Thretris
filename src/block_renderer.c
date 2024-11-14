#include "block_renderer.h"

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,
};

block_renderer_t *block_renderer_create() {
    block_renderer_t *renderer = malloc(sizeof(block_renderer_t));

    glGenVertexArrays(1, &renderer->va);
    glBindVertexArray(renderer->va);

    glGenBuffers(1, &renderer->vb);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &renderer->eb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->eb);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    return renderer;
}

void block_renderer_free(block_renderer_t *renderer) {
    free(renderer);
}

void block_renderer_draw(block_renderer_t *renderer) {
    glBindVertexArray(renderer->va);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);
}