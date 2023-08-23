var canvas = document.getElementById("webgl-context");
var gl = canvas.getContext("webgl");
var glext = gl.getExtension("OES_vertex_array_object");

if (glext) {
    gl["createVertexArray"] = function() { return glext["createVertexArrayOES"](); };
    gl["deleteVertexArray"] = function(vao) { glext["deleteVertexArrayOES"](vao); };
    gl["bindVertexArray"]   = function(vao) { glext["bindVertexArrayOES"](vao); };
    gl["isVertexArray"]     = function(vao) { return glext["isVertexArrayOES"](vao); };
}

class vokeprogram {
    constructor(shaders) {
        this.id = gl.createProgram();
        shaders.forEach(shaderjson => {
            const shader = gl.createShader(shaderjson.stage);
            gl.shaderSource(shader, shaderjson.src);
            gl.compileShader(shader);
            gl.attachShader(this.id, shader);
        });

        gl.linkProgram(this.id);
    }

    setuniformfloat(uniformname, val) {
        gl.uniform1f(gl.getUniformLocation(this.id, uniformname), val);
    }

    setuniformvec2(uniformname, vec) {
        gl.uniform2f(gl.getUniformLocation(this.id, uniformname), vec[0], vec[1]);
    }

    setuniformmat4(uniformname, mat) {
        gl.uniformMatrix4fv(gl.getUniformLocation(this.id, uniformname), false, mat);
    }

    invoke() {
        gl.useProgram(this.id);    
    }

    revoke() {
        gl.useProgram(null);
    }
};

class vokebuffer {
    constructor() {
        this.buffermap = new Map();
        this.contextbufferinfo = [];
        this.indexingrendering = false;
        this.vao = 0;
        this.stride = [];
        this.primitive = [];
    }

    setstride(x, y, z) {
        this.stride[0] = x;
        this.stride[1] = y;
        this.stride[2] = z;
    }

    setprimitive(array) {
        this.primitive[0] = array;
    }

    invoke() {
        if (this.vao == 0) {
            this.vao = gl.createVertexArray();
        }

        gl.bindVertexArray(this.vao);
    }

    revoke() {
        gl.bindVertexArray(null);
    }

    bind(key, buffertype) {
        if (!this.buffermap.has(key)) {
            this.buffermap[key] = gl.createBuffer();
        }

        gl.bindBuffer(buffertype[0], this.buffermap[key]);
        this.contextbufferinfo = buffertype;

        if (buffertype[0] == gl.ELEMENT_ARRAY_BUFFER) {
            this.indexingrendering = true;
            this.primitive[1] = buffertype[1];
        }
    }

    send(data, mode) {
        gl.bufferData(this.contextbufferinfo[0], data, mode);
    }

    edit(bufferstride, data) {
        gl.bufferSubData(this.contextbufferinfo[0], bufferstride, data)
    }

    attach(location, vec, locationStride) {
        gl.enableVertexAttribArray(location);
        gl.vertexAttribPointer(location, vec, this.contextbufferinfo[1], false, locationStride[0], locationStride[1]);
    }

    unbind() {
        gl.bindBuffer(this.contextbufferinfo[0], 0);
    }

    draw() {
        if (this.indexingrendering) {
            gl.drawElements(this.primitive[0], this.stride[1], this.primitive[1], this.stride[0]);
        } else {
            gl.drawArrays(this.primitive[0], this.stride[0], this.stride[1]);
        }
    }
}