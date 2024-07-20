#include "renderer.h"

void _renderer_use_shader(struct Renderer *self, enum ShaderType shader) {
    if (shader == self->current_shader) {
        return;
    }
    self->current_shader = shader;
    self->shader = self->shaders[shader];
    glUseProgram(self->shader.handle);
}

void renderer_init(struct Renderer *self) {
    *self = (struct Renderer) {0};
    self->current_shader = SHADER_NONE;

    // Create and compile GLSL program from shader files. 
    struct Shader shader;
    shader.handle = LoadShaders("res/shaders/SimpleVertexShader.vs", "res/shaders/SimpleFractureShader.fs");
    self->shaders[SIMPLE_SHADER] = shader;
    // OTHER SHADER TYPES HERE!!!

    // Create vertex array object
    struct VAO vertArr = vao_create();
    // Bind vao
    vao_bind(vertArr);
    // Set vao for renderer
    self->vao = vertArr;
    
    // Generate vertex buffer object
    struct VBO vertBuff = vbo_create();
    // Bind vertex buffer
    vbo_bind(vertBuff);
    // Give vertices to OpenGL
    vbo_buff();
    // Set vbo for renderer
    self->vbo = vertBuff;
}


void renderer(struct Renderer *self) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set current shader
    _renderer_use_shader(self, SIMPLE_SHADER);

    GLuint attribute = 0; // Shader layout attribute
    // Set current vao to draw.
    vao_enable(attribute);
    vao_bind(self->vao);
    vao_attrib(attribute, 3, GL_FLOAT, GL_FALSE, 0/*, (void*)0*/);
    // Draw arrays
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Disable current vao
    vao_disable(attribute);

}
