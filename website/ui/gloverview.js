var canvas = document.getElementById("webgl-context");

canvas.style.width = "100%";
canvas.style.height = "100%";

canvas.width = 1920;
canvas.height = 1080;

var pipelineprogram = new vokeprogram([
{
    src: `
    attribute vec2 aPos;

    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
    `,
    stage: gl.VERTEX_SHADER
},
{
    src:`
    precision mediump float;
    uniform float uDelta;
    uniform float uIntensity;

    float rand(vec2 co) {
        return fract(tan(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
    }
    
    vec3 hash3(vec3 n) {
        return fract(sin(n) * 1399763.5453123);
    }
    
    vec3 hpos(vec3 n) {
        return hash3(vec3(dot(n, vec3(157.0, 113.0, 271.0)), dot(n, vec3(311.0, 337.0, 179.0)), dot(n, vec3(271.0, 557.0, 431.0))));
    }
    
    vec4 mod289(vec4 x) {
        return x - floor(x * (1.0 / 289.0)) * 289.0;
    }
    
    vec4 permute(vec4 x) {
        return mod(((x * 34.0) + 1.0) * x, 289.0);
    }
    
    vec4 taylorInvSqrt(vec4 r) {
        return 1.79284291400159 - 0.85373472095314 * r;
    }
    
    vec2 fade(vec2 t) {
        return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
    }
    
    float noise4D(vec2 p) {
        vec4 Pi = floor(p.xyxy) + vec4(0.0, 0.0, 0.0, 1.0);
        vec4 Pf = fract(p.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    
        Pi = mod289(Pi);
    
        vec4 ix = Pi.xzxz;
        vec4 iy = Pi.yyww;
        vec4 fx = Pf.xzxz;
        vec4 fy = Pf.yyww;
    
        vec4 i = permute(permute(ix) + iy);
        vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0;
        vec4 gy = abs(gx) - 0.5;
        vec4 tx = floor(gx + 0.5);
        gx = gx - tx;
    
        vec2 g00 = vec2(gx.x, gy.x);
        vec2 g10 = vec2(gx.y, gy.y);
        vec2 g01 = vec2(gx.z, gy.z);
        vec2 g11 = vec2(gx.w, gy.w);
        vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
        g00 *= norm.x;
        g01 *= norm.y;
        g10 *= norm.z;
        g11 *= norm.z;
    
        float n00 = dot(g00, vec2(fx.x, fy.y));
        float n10 = dot(g10, vec2(fx.y, fy.y));
        float n01 = dot(g01, vec2(fx.z, fy.z));
        float n11 = dot(g11, vec2(fx.w, fy.w));
    
        vec2 fade_xy = fade(Pf.xy);
        vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
        float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
        return 2.3 * n_xy;
    }
    
    float noise(vec2 st) {
        vec2 i = floor(st);
        vec2 f = fract(st);
    
        float a = rand(i);
        float b = rand(i + vec2(1.0, 0.0));
        float c = rand(i + vec2(0.0, 1.0));
        float d = rand(i + vec2(1.0, 1.0));
    
        vec2 u = f * f * (3.0 - 2.0 * f);
        return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
    }

    void main() {
        float i  = uIntensity;
        float f  = (noise(vec2(length((rand(vec2(tan(0.0002), 6766.0))) / fract(uDelta * 0.2) - tan(cos((gl_FragCoord.yx * 2.0) * fract(0.020))) * fract(0.09 * uDelta)))));
        float f2 = (noise(vec2(length((rand(vec2(tan(0.0002), 6766.0))) / sin(uDelta * 0.002) / cos(uDelta * 0.002) - sin(tan((gl_FragCoord.yx) * fract(0.020))) * sin(0.09 * uDelta)))));

        gl_FragColor = vec4(f2, f, f2, f2);
        //gl_FragColor = (vec4(fract(f), rand(vec2((rand(vec2(666.0, sin(2.0)))))) / f, 10.0, 1.0));
        gl_FragColor = mix(gl_FragColor, vec4(rand(vec2(222.0, 666.02)) / f2 / 0.26 * i, f - ((0.333666 * i) / uDelta), f2 / (666.0 * i) * uDelta, f), length(gl_FragColor.x / f / f2 / cos(uDelta * 0.2)));
        gl_FragColor = mix(gl_FragColor, vec4(f2 - f, f2 / f, f2 * f, 1.0), length(f * f2 / cos(uDelta * 0.2)));

        f = (noise(vec2(length((rand(vec2(sin(0.0002), 6766.0))) / tan(uDelta * 0.2 * i) - fract(sin((gl_FragCoord.yx) * fract(0.020 * i))) * fract(0.09 * uDelta)))));
        gl_FragColor = (vec4(fract(f), rand(vec2((rand(vec2(666.0, sin(2.0)))))) / f, 10.0, 1.0));
        gl_FragColor = mix(gl_FragColor, vec4(rand(vec2(f, 100.0*100.0 / tan(2.0))) / f * 0.343, f - 0.32, gl_FragCoord.y / 21312.0, f), length(gl_FragColor.x / f * cos(uDelta * 0.2)));
        gl_FragColor.w = 1.0;
        gl_FragColor = mix(gl_FragColor, vec4(f2 - f * i, f2 / f * i, f2 * f * i, 1.0), length(f * f2 / cos(uDelta * 0.2)));
    }
    `,
    stage: gl.FRAGMENT_SHADER
}
]);

var quad = new vokebuffer();
var quadvertices = [
    -1.0, -1.0,
    -1.0,  1.0,
     1.0,  1.0,
     1.0,  1.0,
     1.0, -1.0,
    -1.0, -1.0
];

quad.invoke();
quad.bind(0, [gl.ARRAY_BUFFER, gl.FLOAT]);                 // "criamos um buffer", e definimos o tipo do primitivo a ser carregado
quad.send(new Float32Array(quadvertices), gl.STATIC_DRAW); // "carrega para a GPU"
quad.attach(0, 2, [0, 0]);                                 // liga no layout da shader vertex shader
quad.revoke();

quad.setprimitive(gl.TRIANGLES);
quad.setstride(0, 6, 0);

var delta = Math.random() * 2.0;
var intensity = 1.0;
var lastkeydown = 0;

document.addEventListener("keydown", function(event) {
    lastkeydown = event.key;
});

document.addEventListener("keyup", function(event) {
    lastkeydown = event.key == lastkeydown ? "" : lastkeydown;
});

function onrender() {
    if (this.lastkeydown == "ArrowRight") {
        this.delta += 0.016;
    } else if (this.lastkeydown == "ArrowLeft") {
        this.delta -= 0.016;
    }

    if (this.lastkeydown == "ArrowUp") {
        this.intensity += 0.016;
    } else if (this.lastkeydown == "ArrowDown") {
        this.intensity -= 0.016;
    }

    gl.viewport(0, 0, canvas.width, canvas.height); // definimos o viewport do site
    gl.clearColor(0.0, 0.0, 0.0, 1.0);              // definimos a cor do background
    gl.clear(gl.COLOR_BUFFER_BIT);                  // limpamos os buffers passados da tela
    gl.enable(gl.BLEND);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

    pipelineprogram.invoke(); // habilitamos o programa do pipeline
    pipelineprogram.setuniformfloat("uDelta", this.delta); // atualizamos o uniform buffer com o valor continuo this.delta.
    pipelineprogram.setuniformfloat("uIntensity", this.intensity);

    quad.invoke(); // ligamos o buffer q queremos renderizar
    quad.draw(); // draw call
    quad.revoke();

    // desligamos o pipeline
    pipelineprogram.revoke();

    // """ Swap buffers """
    requestAnimationFrame(onrender);
}

requestAnimationFrame(onrender);