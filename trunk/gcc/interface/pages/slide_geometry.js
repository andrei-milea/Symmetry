
var SlideGeom = function() {
	this.isBack = true;

	this.mvtype = {
		RIGHT : 0,
		LEFT :1,
		DOWN :2,
		STOP :3
	};

	this.move = this.mvtype.STOP;

	this.verticesRect = [-5.5, 5.0, -25.0,
							5.5, 5.0, -25.0,
							-5.5, -5.0, -25.0,
							5.5, -5.0, -25.0];

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
		if(this.isBack === true && this.move === this.mvtype.STOP)
			return;

		this.releaseBuffers(gl);
		this.initBuffers(gl);

		gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
		gl.enable(gl.BLEND);
		gl.disable(gl.DEPTH_TEST);
		gl.uniform1f(gl.ShaderProgram.alphaUniform, this.slideTexture.alpha)

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

	this.moveBackLeft = function() {
		this.verticesRect = [-5.5, 5.0, -4.5,
							5.5, 5.0, -4.5,
							-5.5, -5.0, -4.5,
							5.5, -5.0, -4.5];
		this.move = this.mvtype.LEFT;
		this.isBack = true;
	}

	this.moveBackRight = function() {
		this.verticesRect = [-5.5, 5.0, -4.5,
							5.5, 5.0, -4.5,
							-5.5, -5.0, -4.5,
							5.5, -5.0, -4.5];
		this.move = this.mvtype.RIGHT;
		this.isBack = true;
	}
	this.moveFrontLeft = function() {
		this.verticesRect = [7.0, 5.0, -25.0,
							18.0, 5.0, -25.0,
							7.0, -5.0, -25.0,
							18.0, -5.0, -25.0];
		this.move = this.mvtype.LEFT;
		this.isBack = false;
	}

	this.moveFrontRight = function() {
		this.verticesRect = [-18.0, 5.0, -25.0,
							-7.0, 5.0, -25.0,
							-18.0, -5.0, -25.0,
							-7.0, -5.0, -25.0];

		this.move = this.mvtype.RIGHT;
		this.isBack = false;
	}

	this.initFall = function() {
		this.verticesRect = [-5.5, 16.0, -4.5,
							5.5, 16.0, -4.5,
							-5.5, 6.0, -4.5,
							5.5, 6.0, -4.5];

		this.move = this.mvtype.DOWN;
		this.isBack = false;
		this.slideTexture.alpha = 1;
	}

	this.moveDown = function(elapsedTime) {
		this.verticesRect[1] -= elapsedTime / 70;
		this.verticesRect[4] -= elapsedTime / 70;
		this.verticesRect[7] -= elapsedTime / 70;
		this.verticesRect[10] -= elapsedTime / 70;

		if(this.verticesRect[1] < 5) {
			this.verticesRect[1] = 5;
			this.verticesRect[4] = 5;
			this.verticesRect[7] = -5;
			this.verticesRect[10] = -5;
			this.move = this.mvtype.STOP;
		}
	}

	this.moveFront = function(elapsedTime) {
		this.verticesRect[2] += elapsedTime / 70;
		this.verticesRect[5] += elapsedTime / 70;
		this.verticesRect[8] += elapsedTime / 70;
		this.verticesRect[11] += elapsedTime / 70;
		this.slideTexture.alpha += elapsedTime / 1500;

		if(this.slideTexture.alpha > 1)
			this.slideTexture.alpha = 1;
		if(this.verticesRect[2] > -4.5) {
			this.verticesRect = [-5.5, 5.0, -4.5,
							5.5, 5.0, -4.5,
							-5.5, -5.0, -4.5,
							5.5, -5.0, -4.5];
			this.slideTexture.alpha = 1;
			this.move = this.mvtype.STOP;
		}
	}

	this.moveBack = function(elapsedTime) {
		this.verticesRect[2] -= elapsedTime / 50;
		this.verticesRect[5] -= elapsedTime / 50;
		this.verticesRect[8] -= elapsedTime / 50;
		this.verticesRect[11] -= elapsedTime / 50;
		this.slideTexture.alpha -= elapsedTime / 1000;

		if(this.slideTexture.alpha < 0)
			this.slideTexture.alpha = 0;
		if(this.verticesRect[2] < -50) {
			this.verticesRect[2] = -50;
			this.verticesRect[5] = -50;
			this.verticesRect[8] = -50;
			this.verticesRect[11] = -50;
			this.slideTexture.alpha = 0;
			this.move = this.mvtype.STOP;
		}
		
	}

	this.moveLeft = function(elapsedTime) {
		this.verticesRect[0] -= elapsedTime / 120;
		this.verticesRect[3] -= elapsedTime / 120;
		this.verticesRect[6] -= elapsedTime / 120;
		this.verticesRect[9] -= elapsedTime / 120;
	}

	this.moveRight = function(elapsedTime) {
		this.verticesRect[0] += elapsedTime / 120;
		this.verticesRect[3] += elapsedTime / 120;
		this.verticesRect[6] += elapsedTime / 120;
		this.verticesRect[9] += elapsedTime / 120;
	}

	this.animate = function(elapsedTime) {
		if(this.move !== this.mvtype.STOP && this.isBack === false) {	//move front
			if(this.move === this.mvtype.DOWN) {
				this.moveDown(elapsedTime);
			}
			else {
				this.moveFront(elapsedTime);
				if(this.move === this.mvtype.RIGHT)
					this.moveRight(elapsedTime);
				else if(this.move === this.mvtype.LEFT)
					this.moveLeft(elapsedTime);
			}
		}
		else if(this.move !== this.mvtype.STOP && this.isBack === true) {	//move back
			this.moveBack(elapsedTime);
			if(this.move === this.mvtype.RIGHT)
				this.moveRight(elapsedTime);
			else
				this.moveLeft(elapsedTime);
		}
	}

	this.setSlideData = function(gl, slide_data) {
		if(this.slideTexture !== null)
			gl.deleteTexture(this.slideTexture);
		this.slideTexture = gl.createTexture();
		this.slideTexture.alpha = 0;
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

