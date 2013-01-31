var LinEq = function() {
	
	var isPlane = false;

	var vertexPositionBuffer;
	var vertices = [];

	var mvMatrixStack = [];
	var mvMatrix;
	var pMatrix;

	var line_color = [0.0, 0.8, 0.1, 1.0];
	var plane_color = [0.1, 0.5, 0.1, 0.5];

	function highlight() {
		line_color = [0.8, 0.1, 0.3, 1.0];
		plane_color = [0.7, 0.1, 0.1, 0.5];
	}

	function unhighlight() {
		line_color = [0.0, 0.8, 0.1, 1.0];
		plane_color = [0.1, 0.5, 0.1, 0.5];
	}

	function set2DEquation(x, y, r) {
		vertices.push(3.0, (r - x * 3.0) / y, 0.0);
		vertices.push((r - y * 3.0) / x, 3.0, 0.0);
	}

	function set3DEquation(x, y, z, r) {
		vertices.push(2.0, 3.0, (r - (x * 2.0) - (y * 3.0) ) / z);
		vertices.push(3.0, 2.0, (r - (x * 3.0) - (y * 2.0) ) / z);
		isPlane = true;
	}

	function setCamera(mv_matrix, p_matrix) {
		mvMatrix = mv_matrix;
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

	function draw(gl) {
		if(isPlane)
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
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, line_color[0], line_color[1], line_color[2], line_color[3]);

		gl.drawArrays(gl.LINES, 0, 2);
	}

	function initBuffers(gl) {
		//position buffer
		vertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	}

	function releaseBuffers() {
		gl.deleteBuffer(vertexPositionBuffer);
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
		set2DEquation : set2DEquation,
		set3DEquation : set3DEquation,
		highlight : highlight,
		unhighlight : unhighlight
	}
};


