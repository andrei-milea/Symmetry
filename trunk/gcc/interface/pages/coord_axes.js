var CoordAxes = function() {
	
	var vertices = [

		//OX
		-6.0 , 0.0, 0.0,
		6.0, 0.0, 0.0,

		-5.0, 0.1, 0.0,
		-5.0, -0.1, 0.0,

		-4.0, 0.1, 0.0,
		-4.0, -0.1, 0.0,

		-3.0, 0.1, 0.0,
		-3.0, -0.1, 0.0,

		-2.0, 0.1, 0.0,
		-2.0, -0.1, 0.0,

		-1.0, 0.1, 0.0,
		-1.0, -0.1, 0.0,

		5.0, 0.1, 0.0,
		5.0, -0.1, 0.0,

		4.0, 0.1, 0.0,
		4.0, -0.1, 0.0,

		3.0, 0.1, 0.0,
		3.0, -0.1, 0.0,

		2.0, 0.1, 0.0,
		2.0, -0.1, 0.0,

		1.0, 0.1, 0.0,
		1.0, -0.1, 0.0,


		//OY
		0.0, -6.0, 0.0,
		0.0, 6.0, 0.0,

		-0.1, -5.0, 0.0,
		0.1, -5.0, 0.0,

		-0.1, -4.0, 0.0,
		0.1, -4.0, 0.0,

		-0.1, -3.0, 0.0,
		0.1, -3.0, 0.0,

		-0.1, -2.0, 0.0,
		0.1, -2.0, 0.0,

		-0.1, -1.0, 0.0,
		0.1, -1.0, 0.0,

		-0.1, 5.0, 0.0,
		0.1, 5.0, 0.0,

		-0.1, 4.0, 0.0,
		0.1, 4.0, 0.0,

		-0.1, 3.0, 0.0,
		0.1, 3.0, 0.0,

		-0.1, 2.0, 0.0,
		0.1, 2.0, 0.0,

		-0.1, 1.0, 0.0,
		0.1, 1.0, 0.0,

		//OZ
		0.0, 0.0, -6.0,
		0.0, 0.0, 6.0,

		-0.1, 0.0, -5.0,
		0.1, 0.0, -5.0,

		-0.1, 0.0, -4.0,
		0.1, 0.0, -4.0,

		-0.1, 0.0, -3.0,
		0.1, 0.0, -3.0,

		-0.1, 0.0, -2.0,
		0.1, 0.0, -2.0,

		-0.1, 0.0, -1.0,
		0.1, 0.0, -1.0,

		-0.1, 0.0, 5.0,
		0.1, 0.0, 5.0,

		-0.1, 0.0, 4.0,
		0.1, 0.0, 4.0,

		-0.1, 0.0, 3.0,
		0.1, 0.0, 3.0,

		-0.1, 0.0, 2.0,
		0.1, 0.0, 2.0,

		-0.1, 0.0, 1.0,
		0.1, 0.0, 1.0

		];

	var arrows = [
		6.0, 0.0, 0.0,
		5.9, -0.1, 0.0,
		5.9, 0.1, 0.0,

		0.0, 6.0, 0.0,
		-0.1, 5.9, 0.0,
		0.1, 5.9, 0.0,
		
		0.0, 0.0, 6.0,
		-0.1, 0.0, 5.9,
		0.1, 0.0, 5.9	
		];

	var xyz = [
		5.152, -0.2, 0.0,
		5.0, -0.2, 0.0,
		5.152, -0.4, 0.0,
		5.0, -0.4, 0.0,

//		-0.3, 5.0, 0.0,
//		-0.452, 5.0, 0.0,
//		-0.3, 4.8, 0.0,
//		-0.452, 4.8, 0.0,
//
//		-0.3, 0.0, 5.1,
//		-0.452, 0.0, 5.1,
//		-0.3, -0.2, 5.1,
//		-0.452, -0.2, 5.1
		];

	var texture_coords = [];

	var axes_3D = false;

	var vertexPositionBuffer;
	var arrowPositionBuffer;
	var xyzPositionBuffer;
	var vertexTextureBuffer;

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
		Letters.init();
		texture_coords = texture_coords.concat(Letters.pos[10]);
//		texture_coords = texture_coords.concat(Letters.pos[11]);
//		texture_coords = texture_coords.concat(Letters.pos[12]);
	}

	function draw(gl) {
		if(axes_3D)
			draw3d(gl);
		else
			draw2d(gl);
	}

	function draw3d(gl) {

		//rotate to view the z-axes
		mvPushMatrix();
		mat4.rotate(mvMatrix, degToRad(10), [1, 0, 0]);
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

		gl.drawArrays(gl.LINES, 0, 66);

		//prepare arrows buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, arrowPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		gl.drawArrays(gl.TRIANGLES, 0, 9);

		drawXYZ(gl);

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
		gl.vertexAttrib4f(gl.ShaderProgram.vertexColorAttribute, 0.0, 0.0, 0.8, 1.0)

		gl.drawArrays(gl.LINES, 0, 44);

		//prepare arrows buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, arrowPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		gl.drawArrays(gl.TRIANGLES, 0, 6);
	}

	function drawXYZ(gl) {

		setMatrixUniforms(gl);

		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, xyzPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//draw with texture
		gl.uniform1f(gl.ShaderProgram.useTexture, 1.0);

		gl.enableVertexAttribArray(gl.ShaderProgram.vertexTextureAttribute);
		gl.disableVertexAttribArray(gl.ShaderProgram.vertexColorAttribute);

		//set texture
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, gl.fntTexture);
		gl.uniform1i(gl.ShaderProgram.shaderSamplerUniform, 0);

		gl.enable(gl.DEPTH_TEST);
		gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
		gl.enable(gl.BLEND);

		gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
		//gl.drawArrays(gl.TRIANGLE_STRIP, 4, 4);
		//gl.drawArrays(gl.TRIANGLE_STRIP, 8, 4);
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

		//xyz buffer
		xyzPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, xyzPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(xyz), gl.STATIC_DRAW);

		//texture buffer 
		vertexTextureBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(texture_coords), gl.STATIC_DRAW);

	}

	function releaseBuffers(gl) {
		gl.deleteBuffer(vertexPositionBuffer);
		gl.deleteBuffer(arrowPositionBuffer);
		gl.deleteBuffer(xyzPositionBuffer);
		gl.deleteBuffer(vertexTextureBuffer);

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


