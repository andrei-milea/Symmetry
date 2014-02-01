
var SlideGeom = function() {
	this.isBack = true;
	this.move_active = false;

	this.verticesRect = [-5.5, 5.0, -12.0,
							5.5, 5.0, -12.0,
							-5.5, -5.0, -12.0,
							5.5, -5.0, -12.0];

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

	this.slideTexture = null;

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
		if(this.isBack === true && this.move_active === false)
			return;
		if(this.move_active === true) {
			this.releaseBuffers(gl);
			this.initBuffers(gl);
		}

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, this.verticesPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//prepare texture buffer for drawing
		gl.uniform1f(gl.ShaderProgram.useTexture, 1.0);

		gl.bindBuffer(gl.ARRAY_BUFFER, this.texturePositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
		gl.bindTexture(gl.TEXTURE_2D, this.slideTexture);
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
	}

	this.moveBack = function() {
		this.move_active = true;
		this.isBack = true;
	}

	this.moveFront = function() {
		this.isBack = false;
		this.move_active = true;
	}

	this.animate = function(elapsedTime) {
		if(this.move_active === true && this.isBack === false) {	//move front
			this.verticesRect[2] += elapsedTime / 100;
			this.verticesRect[5] += elapsedTime / 100;
			this.verticesRect[8] += elapsedTime / 100;
			this.verticesRect[11] += elapsedTime / 100;
			if(this.verticesRect[2] > -6) {
				this.verticesRect[2] = -6;
				this.verticesRect[5] = -6;
				this.verticesRect[8] = -6;
				this.verticesRect[11] = -6;
				this.move_active = false;
			}
		}
		else if(this.move_active === true && this.isBack === true) {	//move back
			this.verticesRect[2] -= elapsedTime / 100;
			this.verticesRect[5] -= elapsedTime / 100;
			this.verticesRect[8] -= elapsedTime / 100;
			this.verticesRect[11] -= elapsedTime / 100;
			if(this.verticesRect[2] < -12) {
				this.verticesRect[2] = -12;
				this.verticesRect[5] = -12;
				this.verticesRect[8] = -12;
				this.verticesRect[11] = -12;
				this.move_active = false;
			}
		}
	}

	this.setSlideData = function(gl, slide_data) {
		if(this.slideTexture !== null)
			gl.deleteTexture(this.slideTexture);
		this.slideTexture = gl.createTexture();
		this.slideTexture.image = new Image();
		this.slideTexture.image.gl = gl;
		this.slideTexture.image.texture = this.slideTexture;
		this.slideTexture.image.onload = function () {
			gl = this.gl;
			gl.bindTexture(gl.TEXTURE_2D, this.texture);
			gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
			gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, this);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
			gl.bindTexture(gl.TEXTURE_2D, null);
		};
		this.slideTexture.image.src = "data:image/png;base64," + slide_data;
	}
}

