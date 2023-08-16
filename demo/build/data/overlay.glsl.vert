#version 450

layout (location = 0) in vec2 aPos;

out vec2 vPos;
out vec4 vRect;

uniform vec4 uRect;

void main() {
    gl_Position = vec4(aPos * vRect.zw + vRect.xy, 0.0f, 1.0f);

    vPos = aPos;
    vRect = vRect;
}