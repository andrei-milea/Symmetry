var Curve = function() {
	var vertexPositionBuffer;
	var vertexIndicesBuffer;
	var vertices = [];
	var indices = [0, 1, 2, 0, 3, 2];
	var segments =20;
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

	function deCasteljau(ctrl_points, points_no, start_idx, delta) {
		if (points_no == 0) return ctrl_points[start_idx];
		var p1 = deCasteljau(ctrl_points,points_no - 1, start_idx, delta);
		var p2 = deCasteljau(ctrl_points,points_no - 1, start_idx + 1, delta);
		return [(1 - delta) * p1[0] + delta * p2[0], (1 - delta) * p1[1] + delta * p2[1]];
	}

	function computePoints(points) {
		var ret_points = [segments];
		var t;
		for (var i = 0; i <= segments; ++i) {        
			delta = 0 + i / segments;
			ret_points[i] = deCasteljau(points, points.length - 1, 0, delta);
		}
		return ret_points;
	}

	function setPoints(points) {
		var generated_points = computePoints(points);
		for (var i = 0; i < generated_points.length; ++i) {
			vertices.push(generated_points[i][0], generated_points[i][1], 0.0);
		}
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

		gl.drawArrays(gl.LINES, 0, 2);
	}

	function initBuffers(gl) {
		//position buffer
		vertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

		vertexIndicesBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, vertexIndicesBuffer);
		gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
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


