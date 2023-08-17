#version 450

layout (location = 0) out vec4 vFragColor;

in vec2 vPos;
in vec4 vRect;

uniform vec4 uColor;

void main() {
    vFragColor = vec4(noise3(uColor.xyz * 0.5f / gl_FragCoord.yxy / uColor.xyz * cos(gl_FragCoord.xyx / vRect.xyw)), 1.0f);
}