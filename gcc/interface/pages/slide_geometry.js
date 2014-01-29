
var SlideGeom = function() {
	this.pending_move = false;

	this.verticesRect = [-3.0, 3.0, -5.0,
							3.0, 3.0, -5.0,
							-3.0, -3.0, -5.0,
							3.0, -3.0, -5.0];

	this.verticesTexture = [0.0, 1.0,
							1.0, 1.0,
							0.0, 0.0,
							1.0, 0.0];

	this.vertexNum = 4;
	this.textureposNum = 4;

	this.verticesPositionBuffer = null;
	this.texturePositionBuffer = null;

	this.mvMatrixStack = [];
	this.mvMatrix = mat4.create();
	this.pMatrix = mat4.create();

	this.setCamera = function(modelview_matrix, proj_matrix) {
		var copy = mat4.create();
		mat4.set(modelview_matrix, copy);
		this.mvMatrix = copy;
		this.pMatrix = proj_matrix;
	}

	this.mvPushMatrix = function() {
		var copy = mat4.create();
		mat4.set(this.mvMatrix, copy);
		this.mvMatrixStack.push(copy);
	}

	this.mvPopMatrix = function() {
		if (this.mvMatrixStack.length == 0) {
			throw "Invalid popMatrix!";
		}
		this.mvMatrix = this.mvMatrixStack.pop();
	}

	this.setMatrixUniforms = function(gl) {
		gl.uniformMatrix4fv(gl.ShaderProgram.pMatrixUniform, false, this.pMatrix);
		gl.uniformMatrix4fv(gl.ShaderProgram.mvMatrixUniform, false, this.mvMatrix);
	}

	this.draw = function(gl) {
		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, this.verticesPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//prepare texture buffer for drawing
		gl.uniform1f(gl.ShaderProgram.useTexture, 1.0);

		gl.bindBuffer(gl.ARRAY_BUFFER, this.texturePositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
		gl.bindTexture(gl.TEXTURE_2D, gl.slideTexture);
		gl.activeTexture(gl.TEXTURE0);
		gl.uniform1i(gl.ShaderProgram.shaderSamplerUniform, 0);

		//handle rotation
		this.mvPushMatrix();

		this.setMatrixUniforms(gl);
		gl.drawArrays(gl.TRIANGLE_STRIP, 0, this.vertexNum);

		//restore the model view matrix
		this.mvPopMatrix();
	}

	this.initBuffers = function(gl) {
		//front position buffer
		this.verticesPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, this.verticesPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.verticesRect), gl.STATIC_DRAW);

		//texture position buffer
		this.texturePositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, this.texturePositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.verticesTexture), gl.STATIC_DRAW);
	}

	this.releaseBuffers = function(gl) {
		gl.deleteBuffer(this.verticesPositionBuffer);
		gl.deleteBuffer(this.texturePositionBuffer);
		gl.deleteTexture(gl.slideTexture);
	}

	this.moveBack = function() {
	}

	this.moveFront = function() {
	}

	this.animate = function(elapsedTime) {
	}

	this.setSlide = function(gl, slide_data) {
		gl.slideTexture = gl.createTexture();
		gl.slideTexture.image = new Image();
		gl.slideTexture.image.onload = function () {
			gl.bindTexture(gl.TEXTURE_2D, gl.slideTexture);
			gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
			gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, this);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
			gl.bindTexture(gl.TEXTURE_2D, null);
		};
		gl.slideTexture.image.src = "data:image/png;base64," + slide_data;
	}
}

