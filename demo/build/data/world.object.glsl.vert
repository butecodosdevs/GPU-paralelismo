#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vPos;
out vec3 vNormal;

uniform mat4 uMatrixProjection;
uniform mat4 uMatrixModel;

void main() {
    gl_Position = uMatrixProjection * vec4(aPos, 1.0f);

    vPos = (uMatrixModel * vec4(aPos, 1.0f)).xyz;
    vNormal = aNormal;
}