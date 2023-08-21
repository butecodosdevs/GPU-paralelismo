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
    vec2 f = (noise2(vec2(length((rand(vec2(9.0f, 6766.0f))) / (uDelta) - tan(tan((gl_FragCoord.yx * 0.2f) * fract(0.060f))) * fract(0.9f)))));
    vFragColor = (vec4(fract( mix(f.x, f.y, 0.5f) ), (rand(vec2((rand(vec2(uDelta, 663.0f)))))).x / f.y, 10.0f, 1.0f));
    vFragColor = mix(vFragColor / f.x, (vec4(((f.x  * sin(uDelta))))), 1.0f);
    vFragColor.w = 0.6f;
}