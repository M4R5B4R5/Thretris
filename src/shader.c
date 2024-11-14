#include "shader.h"

static char *file_src(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Invalid file path");
        return NULL;
    }

    long file_length = 0;
    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *src = malloc(file_length * sizeof(char) + 1);
    src[file_length] = '\0';
    fread(src, file_length, sizeof(char), file);

    fclose(file);
    return src;
}

shader_t shader_create(const char *vertex_path, const char *fragment_path) {
    shader_t shader;
    shader.id = glCreateProgram();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    char *vertex_src = file_src(vertex_path);
    char *fragment_src = file_src(fragment_path);

    glShaderSource(vertex_shader, 1, (const GLchar * const*)&vertex_src, NULL);
    glShaderSource(fragment_shader, 1, (const GLchar * const*)&fragment_src, NULL);

    free(vertex_src);
    free(fragment_src);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);
    glAttachShader(shader.id, vertex_shader);
    glAttachShader(shader.id, fragment_shader);
    glLinkProgram(shader.id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

void shader_use(shader_t shader) {
    glUseProgram(shader.id);
}

void shader_destroy(shader_t shader) {
    glDeleteProgram(shader.id);
}