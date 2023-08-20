#version 450

layout (location = 0) out vec4 vFragColor;

in vec3 vPos;
in vec3 vNormal;

uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform vec3 uMaterialColor;

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 applyUseless() {
    vec3 l = normalize(vPos - uLightPos);
    float albedo = max(dot(l, noise3(vec3(rand(vec2(l.x, l.z)), rand(vec2(l.z, l.y)), rand(vec2(l.x, l.y))))), 0.0f);
    return vec3(noise3(vec3(tan(rand(vec2(l.x, l.z)) / 0.2f), rand(vec2(l.z, l.y)) / 0.9f, rand(vec2(l.x, l.y) / 0.2f))));
}

vec3 applyDiffuseLighting() {
    vec3 l = normalize(vPos - uLightPos);
    float albedo = max(dot(l, vNormal), 0.0f);
    return uMaterialColor * albedo;
}

void main() {
    vFragColor = vec4(1.0f);
}