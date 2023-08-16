#version 450

layout (location = 0) out vec4 vFragColor;

in vec2 vPos;
in vec4 vRect;

uniform vec4 uColor;

void main() {
    vFragColor = uColor;
}