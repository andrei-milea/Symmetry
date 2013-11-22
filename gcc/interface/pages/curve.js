var Curve = function() {
	var vertexPositionBuffer;
	var vertices = [];
	var highlighted = false;

	var mvMatrixStack = [];
	var mvMatrix;
	var pMatrix;

	var line_color = [0.0, 0.8, 0.1, 1.0];

	function highlight() {
		line_color = [0.8, 0.0, 0.1, 1.0];
		highlighted = true;
	}

	function unhighlight() {
		line_color = [0.0, 0.8, 0.1, 1.0];
		highlighted = false;
	}

	function setPoints(points) {
		for (var i = 0; i < points.length; ++i) {
			vertices.push(points[i][0], points[i][1], 0.0);
		}
		vertices.number = points.length;
	}

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

	function draw(gl) {
		setMatrixUniforms(gl);

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//draw without texture
		gl.uniform1f(gl.ShaderProgram.useTexture, 0.0);

		gl.disableVertexAttribArray(gl.ShaderProgram.vertexTextureAttribute);
		gl.disableVertexAttribArray(gl.ShaderProgram.vertexColorAttribute);
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, line_color[0], line_color[1], line_color[2], line_color[3]);

		gl.drawArrays(gl.LINE_STRIP, 0, vertices.number);
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
		setPoints : setPoints,
		highlight : highlight,
		unhighlight : unhighlight
	}
};


