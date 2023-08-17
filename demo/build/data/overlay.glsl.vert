#version 450

layout (location = 0) in vec2 aPos;

out vec2 vPos;
out vec4 vRect;

// As funções glUniform* do OpenGL são para enviar dados para essa shader.
uniform vec4 uRect;
uniform mat4 uMatrixProjection;

void main() {
    // A matrix de projectção é a orthografica.
    // Está sendo feito uma operação de multiplicação entre vetore e matrix.
    gl_Position = uMatrixProjection * vec4((aPos * uRect.zw) + uRect.xy, 0.0f, 1.0f);

    vPos = aPos;
    vRect = uRect;
}