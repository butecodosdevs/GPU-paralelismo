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
    return vec3(gl_FragCoord.xyz * 7777.0f * 0.2f / noise3(vec3(tan(rand(vec2(l.x, l.z)) / 333.0f), rand(vec2(l.z, l.y)) / 2222.0f, rand(vec2(l.x, l.y) / 33.0f))));
}

vec3 applyDiffuseLighting() {
    vec3 l = normalize(vPos - uLightPos);
    float albedo = max(dot(l, vNormal), 0.0f);
    return uMaterialColor * albedo;
}

void main() {
    vFragColor = vec4(1.0f);
}