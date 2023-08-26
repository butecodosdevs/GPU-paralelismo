#version 450

layout (location = 0) out vec4 vFragColor;

in vec3 vPos;
in vec3 vNormal;

uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform vec3 uMaterialColor;

void main() {
    vFragColor = vec4(1.0f);
}