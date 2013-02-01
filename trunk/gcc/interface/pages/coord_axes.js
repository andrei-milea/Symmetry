var CoordAxes = function() {
	
	var vertices = [
		-3.0 , 0.0, 0.0,
		3.0, 0.0, 0.0,

		0.0, -3.0, 0.0,
		0.0, 3.0, 0.0,

		0.0, 0.0, -5.0,
		0.0, 0.0, 3.0
		];

	var arrows = [
		3.0, 0.0, 0.0,
		2.9, -0.1, 0.0,
		2.9, 0.1, 0.0,

		0.0, 3.0, 0.0,
		-0.1, 2.9, 0.0,
		0.1, 2.9, 0.0,
		
		0.0, 0.0, 3.0,
		-0.1, 0.0, 2.9,
		0.1, 0.0, 2.9	
		];

	var axes_3D = false;

	var vertexPositionBuffer;
	var arrowPositionBuffer;

	var mvMatrixStack = [];
	var mvMatrix;
	var pMatrix;

	function setCamera(mv_Matrix, p_matrix) {
		var copy = mat4.create();
		mat4.set(mv_Matrix, copy);
		mvMatrix = copy;
		pMatrix = p_matrix;
	}

	function setMatrixUniforms(gl) {
		gl.uniformMatrix4fv(gl.ShaderProgram.pMatrixUniform, false, pMatrix);
		gl.uniformMatrix4fv(gl.ShaderProgram.mvMatrixUniform, false, mvMatrix);
	}

	function mvPushMatrix() {
		var copy = mat4.create();
		mat4.set(mvMatrix, copy);
		mvMatrixStack.push(copy);
	}

	function degToRad(degrees) {
		return degrees * Math.PI / 180;
	}

	function mvPopMatrix() {
		if (mvMatrixStack.length == 0) {
			throw "Invalid popMatrix!";
		}
		mvMatrix = mvMatrixStack.pop();
	}

	function set3D() {
		axes_3D = true;
	}

	function draw(gl) {
		if(axes_3D)
			draw3d();
		else
			draw2d();
	}

	function draw3d() {
		//rotate to view the z-axes
		mvPushMatrix();
		mat4.rotate(mvMatrix, degToRad(30), [1, 0, 0]);
		mat4.rotate(mvMatrix, degToRad(-30), [0, 1, 0]);

		setMatrixUniforms(gl);

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//draw without texture
		gl.uniform1f(gl.ShaderProgram.useTexture, 0.0);

		gl.disableVertexAttribArray(gl.ShaderProgram.vertexTextureAttribute);
		gl.disableVertexAttribArray(gl.ShaderProgram.vertexColorAttribute);
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, 0.0, 0.0, 0.8, 1.0)

		gl.drawArrays(gl.LINES, 0, 6);

		//prepare arrows buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, arrowPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		gl.drawArrays(gl.TRIANGLES, 0, 9);

		//restore the model view matrix
		mvPopMatrix();
	}

	function draw2d() {
		setMatrixUniforms(gl);

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//draw without texture
		gl.uniform1f(gl.ShaderProgram.useTexture, 0.0);

		gl.disableVertexAttribArray(gl.ShaderProgram.vertexTextureAttribute);
		gl.disableVertexAttribArray(gl.ShaderProgram.vertexColorAttribute);
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, 0.0, 0.0, 0.8, 1.0)

		gl.drawArrays(gl.LINES, 0, 4);

		//prepare arrows buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, arrowPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		gl.drawArrays(gl.TRIANGLES, 0, 6);
	}

	function initBuffers(gl) {
		//position buffer
		vertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

		//arrows buffer
		arrowPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, arrowPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(arrows), gl.STATIC_DRAW);
	}

	function releaseBuffers() {
		gl.deleteBuffer(vertexPositionBuffer);
		gl.deleteBuffer(arrowPositionBuffer);
	}

	function animate() {
		return;
	}

	return {
		initBuffers : initBuffers,
		releaseBuffers : releaseBuffers,
		setCamera : setCamera,
		draw : draw,
		animate : animate,
		set3D : set3D
	}
};


