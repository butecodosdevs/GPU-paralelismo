#version 450

layout (location = 0) out vec4 vFragColor;
uniform vec4 uColor;

void main() {
    // Você recebe o uniform da CPU e atribui a essa shader.
    vFragColor = uColor;
                  // RED GREEN BLUE ALPHA
}