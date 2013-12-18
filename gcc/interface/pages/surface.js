var Surface = function() {
	var vertexPositionBuffer;
	var vertexIndexBuffer;
	var vertices = [];
	var indices = [];
	var line_size = 1;
	var highlighted = false;

	var mvMatrixStack = [];
	var mvMatrix;
	var pMatrix;

	var line_color = [0.0, 0.8, 0.1, 1.0];
	var plane_color = [0.0, 0.5, 0.0, 0.5];

	function highlight() {
		line_color = [0.8, 0.0, 0.1, 1.0];
		highlighted = true;
	}

	function unhighlight() {
		line_color = [0.0, 0.8, 0.1, 1.0];
		highlighted = false;
	}

	function setPoints(points) {
		var first_val = points[0][0];
		var stop = false;
		for (var i = 0; i < points.length; ++i) {
			vertices.push(points[i][0], points[i][2], points[i][1]);
			if((first_val !== points[i][0]) && (stop === false)) {
				line_size = i;
				stop = true;
			}
		}
		vertices.number = points.length/2;
		indices.number = 0;
		var lines = vertices.number / line_size - 1;
		for(idx_line = 0; idx_line < lines; idx_line++) {
			//add degenerate triangles
			var idx_col = 0;
			if(idx_line !== 0) {
				indices.push((idx_line * line_size) + idx_col);
				indices.number++;
			}

			for(idx_col = 0; idx_col < line_size; idx_col++)
				indices.push((idx_line * line_size) + idx_col, (idx_line * line_size) + idx_col + line_size);

			//add degenerate triangles
			if(idx_line + 1 < lines) {
				indices.push((idx_line * line_size) + (idx_col-1) + line_size);
				indices.number++;
			}
			indices.number += 2 * line_size;
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
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, plane_color[0], plane_color[1], plane_color[2], plane_color[3]);

		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);

		gl.drawElements(gl.TRIANGLE_STRIP, indices.number, gl.UNSIGNED_SHORT, 0);

		//draw lines
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, line_color[0], line_color[1], line_color[2], line_color[3]);
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		var lines = vertices.number / line_size;
		for(var idx = 1; idx < lines - 1; idx++) {
			gl.drawArrays(gl.LINE_STRIP, idx * line_size, line_size);
		}
		var cols = vertices.number / line_size;
		for(var idx = 1; idx < cols - 1; idx++) {
			gl.drawArrays(gl.LINE_STRIP, vertices.number + idx * line_size, line_size);
		}
	}

	function initBuffers(gl) {
		//position buffer
		vertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

		//index buffer
		vertexIndexBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);
		gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

	}

	function releaseBuffers() {
		gl.deleteBuffer(vertexPositionBuffer);
		gl.deleteBuffer(vertexIndexBuffer);
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


