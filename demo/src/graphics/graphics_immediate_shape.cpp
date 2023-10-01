#include "graphics_immediate_shape.hpp"

void chorume::graphics_immediate_shape::set_pipeline_program(uint32_t _pipeline_program) {
    this->pipeline_program = _pipeline_program;

    this->uniform_location_rect_id = glGetUniformLocation(this->pipeline_program, "uRect");
    this->uniform_location_color_id = glGetUniformLocation(this->pipeline_program, "uColor");
    this->uniform_location_is_texture_active_id = glGetUniformLocation(this->pipeline_program, "uIsTextureActive");
    this->uniform_location_matrix_projection_id = glGetUniformLocation(this->pipeline_program, "uMatrixProjection");

    if (this->list_buffer_id == 0) {
        // Para gerar um buffer dentro da GPU,
        // precisamos definir um id.

        glGenBuffers(1, &this->buffer_resources_id);
        glGenBuffers(1, &this->buffer_indices_id);
        glGenVertexArrays(1, &this->list_buffer_id);
    
        float resources[8] {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
        };

        uint8_t indices[6] {
            0, 1, 3,
            3, 2, 0
        };

        // Emm especifico, esse ID referencia uma lista de outros
        // buffers. Essa lista de buffers vai ser ligada no programa
        // de shader.
        glBindVertexArray(this->list_buffer_id);

        // Esse ID vai ser encarregado de referenciar,
        // toda vez que for preciso mexer com esse buffer,
        // é preciso ligar o buffer no código para usar ele. 

        glBindBuffer(GL_ARRAY_BUFFER, this->buffer_resources_id);

        // Nas APIs modernas, para enviar dados para esse buffer,
        // é por uma série de etapas. No OpenGL, não é necessario essas
        // etapas, mas vamos fazer aqui.

        // Primeiro alocamos um espaço dentro da VRAM da GPU.
        glBufferData(GL_ARRAY_BUFFER, sizeof(resources), nullptr, GL_STATIC_DRAW);
        
        // Agora damos "fill", preenchendo o espaço vazio com os dados 
        // que queremos enviar.

        // Stride é um conceito de memória, muito usado nas APIs.
        // initial offset stride index é a posição da lista que vai
        // começar a preencher.
        // size index byte é a quantidade em diante que vai ser preenchida.

        uint64_t initial_offset_index_byte = 0;
        uint64_t size_index_byte = sizeof(resources);

        glBufferSubData(GL_ARRAY_BUFFER, initial_offset_index_byte, size_index_byte, resources);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_indices_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
}

void chorume::graphics_immediate_shape::invoke() {
    glUseProgram(this->pipeline_program); // programa do pipeline ligado
    glBindVertexArray(this->list_buffer_id);

    // Esses estados sao os mencionados no processo de rasterizacao

    glDisable(GL_DEPTH_TEST); // depth test desabilitado
    glEnable(GL_BLEND); // blending habilitado
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // definicoes do blending

    this->delta += 0.016f;
    glUniform1f(glGetUniformLocation(this->pipeline_program, "uDelta"), this->delta); // uniforms dinamicos

    glActiveTexture(GL_TEXTURE0);
    glUniformMatrix4fv(this->uniform_location_matrix_projection_id, GL_TRUE, GL_FALSE,
                       &chorume::application.camera.mat_ortho_view[0][0]); // uniforms dinamicos
}

void chorume::graphics_immediate_shape::draw(const glm::vec4 &rect, const glm::vec4 &color, uint32_t texture) {
    glUniform4f(this->uniform_location_rect_id, rect.x, rect.y, rect.z, rect.w); // uniforms dinamicos
    glUniform4f(this->uniform_location_color_id, color.x, color.y, color.z, color.w); // uniforms dinamicos
    glUniform1i(this->uniform_location_is_texture_active_id, texture); // uniforms dinamicos

    if (this->current_texture_bound != texture) {
        this->current_texture_bound = texture;
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr); // draw call
}

void chorume::graphics_immediate_shape::revoke() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glBindVertexArray(0);
    glUseProgram(0); // nenhuma pipeline ligada
}
