#include "block.h"

block_t block_create(vec3 position, float size, vec3 color) {
    block_t block;
    glm_vec3_copy(position, block.position);
    block.size = size;
    glm_vec3_copy(color, block.color);
    return block;
}