#version 450

layout (location = 0) out vec4 vFragColor;

in vec2 vPos;
in vec4 vRect;

uniform vec4 uColor;
uniform float uDelta;

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vFragColor = uColor;
}