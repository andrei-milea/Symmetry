var LinEq = function() {
	
	var isPlane = false;

	var vertexPositionBuffer;
	var vertexIndicesBuffer;
	var vertices = [];
	var indices = [0, 1, 2, 0, 3, 2];
	var highlighted = false;

	var mvMatrixStack = [];
	var mvMatrix;
	var pMatrix;

	var line_color = [0.0, 0.8, 0.1, 1.0];
	var plane_color = [0.0, 0.5, 0.0, 0.5];

	function highlight() {
		line_color = [0.8, 0.0, 0.1, 1.0];
		plane_color = [0.9, 0.5, 0.3, 1.0];
		highlighted = true;
	}

	function unhighlight() {
		line_color = [0.0, 0.8, 0.1, 1.0];
		plane_color = [0.0, 0.5, 0.0, 0.5];
		highlighted = false;
	}

	function set2DEquation(x, y, r) {
		vertices.push(-3.0, (r - x * (-3.0)) / y, 0.0);
		vertices.push(3.0, (r - x * (3.0)) / y, 0.0);
	}

	function set3DEquation(x, y, z, r) {
		var normal = [x, y, z];
		var z_axis = [0, 0, 1];
		var temp = vec3.create([0.0, 0.0, 0.0]);
		var u, v;
		if(vec3.length(vec3.cross(normal, z_axis, temp)) < 1.0) {
			u = [1, 0, 0];
			v = [0, 1, 0];
		}
		else {
			var temp3 = vec3.create([0.0, 0.0, 0.0]);
			u = vec3.cross(normal, z_axis, temp3); //[y - z, z - x, x - y];
			v = vec3.cross(normal, [y - z, z - x, x - y], temp); 
		}
		
		vec3.normalize(u);
		vec3.normalize(v);

		var zfar = 1.0 + (1 / Math.max(vec3.length(v), r));

		//var P0 = [0.0, 0.0, -r / z]; 
		temp = vec3.create([0.0, 0.0, 0.0]);
		vec3.normalize(normal);
		var P0 = vec3.scale(normal, r, temp);
		var temp2 = vec3.create([0.0, 0.0, 0.0]);
		var fu =  vec3.scale(u, zfar, temp2);
		var temp1 = vec3.create([0.0, 0.0, 0.0]);
		var fv =  vec3.scale(v, zfar, temp1);
		vertices.push(P0[0] - fu[0] - fv[0], P0[1] - fu[1] - fv[1], P0[2] - fu[2] - fv[2]);
		vertices.push(P0[0] + fu[0] - fv[0], P0[1] + fu[1] - fv[1], P0[2] + fu[2] - fv[2]);
		vertices.push(P0[0] + fu[0] + fv[0], P0[1] + fu[1] + fv[1], P0[2] + fu[2] + fv[2]);
		vertices.push(P0[0] - fu[0] + fv[0], P0[1] - fu[1] + fv[1], P0[2] - fu[2] + fv[2]);

		isPlane = true;
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
		if(isPlane)
			draw3d(gl);
		else
			draw2d(gl);
	}

	function draw3d(gl) {
		//rotate to view the z-axes
		mvPushMatrix();
		mat4.rotate(mvMatrix, degToRad(30), [1, 0, 0]);
		mat4.rotate(mvMatrix, degToRad(-30), [0, 1, 0]);

		setMatrixUniforms(gl);

		gl.enable(gl.DEPTH_TEST);
		if(highlighted === false) {
			gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
			gl.enable(gl.BLEND);
		}
		else {
			gl.disable(gl.BLEND);
		}

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//draw without texture
		gl.uniform1f(gl.ShaderProgram.useTexture, 0.0);

		gl.disableVertexAttribArray(gl.ShaderProgram.vertexTextureAttribute);
		gl.disableVertexAttribArray(gl.ShaderProgram.vertexColorAttribute);
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, line_color[0], line_color[1], line_color[2], line_color[3]);

		gl.drawArrays(gl.LINE_LOOP, 0, 4);

		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, vertexIndicesBuffer);
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, plane_color[0], plane_color[1], plane_color[2], plane_color[3]);
		gl.drawElements(gl.TRIANGLE_STRIP, 6, gl.UNSIGNED_SHORT, 0);

		//restore the model view matrix
		mvPopMatrix();
	}

	function draw2d(gl) {
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

	function releaseBuffers(gl) {
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


