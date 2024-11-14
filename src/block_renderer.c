#include "block_renderer.h"

static float vertices[] = {
    // FRONT
    -0.5f, -0.5f, 0.5f,
     0.5f, -0.5f, 0.5f,
     0.5f,  0.5f, 0.5f,
    -0.5f,  0.5f, 0.5f,

    // BACK
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    // LEFT
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    // RIGHT
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,

    // TOP
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
    
    // BOTTOM
    -0.5f,  -0.5f,  0.5f,
    -0.5f,  -0.5f, -0.5f,
     0.5f,  -0.5f, -0.5f,
     0.5f,  -0.5f,  0.5f,
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    8, 9, 10,
    10, 11, 8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20,
};

unsigned int wire_indices[] = {
    0, 1, // FRONT
    1, 2,
    2, 3,
    3, 0,

    4, 5, // BACK
    5, 6,
    6, 7,
    7, 4,

    0, 4, // LEFT
    1, 5,
    2, 6,
    3, 7,

    4, 5, // RIGHT
    5, 6,
    6, 7,
    7, 4,

    0, 3, // TOP
    1, 2,

    4, 7, // BOTTOM
    5, 6
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

    glLineWidth(3.0f);
    glGenBuffers(1, &renderer->wire_eb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->wire_eb);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wire_indices), wire_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    return renderer;
}

void block_renderer_free(block_renderer_t *renderer) {
    free(renderer);
}

static void block_renderer_render_wire(block_renderer_t *renderer, block_t block, shader_t shader) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->wire_eb);

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, block.position);
    glm_scale(model, (vec3) {1.01f, 1.01f, 1.01f});

    shader_set_int(shader, "vCol", (vec3) {1.0f, 0.0f, 1.0f});
    shader_set_mat4fv(shader, model, "model");

    glDrawElements(GL_LINES, sizeof(indices), GL_UNSIGNED_INT, NULL);
}

static void block_renderer_render_block(block_renderer_t *renderer, block_t block, shader_t shader) {
    glBindVertexArray(renderer->va);
    shader_use(shader);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->eb);

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, block.position);

    shader_set_int(shader, "vCol", block.color);
    shader_set_mat4fv(shader, model, "model");

    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);
}

void block_renderer_render(block_renderer_t *renderer, block_t block, shader_t shader) {
    block_renderer_render_block(renderer, block, shader);
}

void block_renderer_render_debug(block_renderer_t *renderer, block_t block, shader_t shader) {
    block_renderer_render_block(renderer, block, shader);
    block_renderer_render_wire(renderer, block, shader);
}