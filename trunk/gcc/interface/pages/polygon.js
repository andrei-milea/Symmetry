var Polygon = function() {
	
	var rotation = 0,
		reflection = 0;

	var angle = 0,
	   	refangle = 0,
		pending_move = 0,
		rotationSpeed = 0;

	var vertices = [];
		textCoords = [];
		rottextCoords = [];
		textureCoords = [];
		blacktextureCoords = [];

	var vertexNum,
		textposNum = 4,
		textureposNum = 4;

	var vertexPositionBuffer,
		vertexTextureBuffer,
		blackTextureBuffer,
		vertexTextBuffer,
		rotVertexTextBuffer;

	var mvMatrixStack = [];

	var mvMatrix;
	var pMatrix;

	function setCamera(mv_matrix, p_matrix) {
		mvMatrix = mv_matrix;
		pMatrix = p_matrix;
	}

	function mvPushMatrix() {
		var copy = mat4.create();
		mat4.set(mvMatrix, copy);
		mvMatrixStack.push(copy);
	}

	function mvPopMatrix() {
		if (mvMatrixStack.length == 0) {
			throw "Invalid popMatrix!";
		}
		mvMatrix = mvMatrixStack.pop();
	}

	function setMatrixUniforms(gl) {
		gl.uniformMatrix4fv(gl.ShaderProgram.pMatrixUniform, false, pMatrix);
		gl.uniformMatrix4fv(gl.ShaderProgram.mvMatrixUniform, false, mvMatrix);
	}

	function degToRad(degrees) {
		return degrees * Math.PI / 180;
	}

	function Draw(gl) {
		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

		//handle rotation
		mvPushMatrix();
		mat4.rotate(mvMatrix, degToRad(refangle), [1, 0, 0]);
		mat4.rotate(mvMatrix, degToRad(angle), [0, 0, 1]);

		//prepare texture buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, blackTextureBuffer);
		gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, gl.blackTexture);
		gl.uniform1i(gl.ShaderProgram.shaderSamplerUniform, 0);

		setMatrixUniforms(gl);
		gl.drawArrays(gl.LINE_LOOP, 0, vertexNum);

		//restore the model view matrix
		mvPopMatrix();

		DrawText(gl);
	}

	function DrawText(gl) {

		for(var i = 0; i < vertexNum; i++) {
			//prepare position buffer for drawing
			gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextBuffer);
			gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

			//prepare texture buffer for drawing
			gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
			gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
			gl.activeTexture(gl.TEXTURE0);
			gl.bindTexture(gl.TEXTURE_2D, gl.fntTexture);
			gl.uniform1i(gl.ShaderProgram.shaderSamplerUniform, 0);

			//handle rotation
			mvPushMatrix();

			setMatrixUniforms(gl);

			gl.drawArrays(gl.TRIANGLE_STRIP, i*4, textposNum);

			//restore the model view matrix
			mvPopMatrix();
		}
		//draw rotated text
		for(var i = 0; i < vertexNum; i++) {
			//prepare position buffer for drawing
			gl.bindBuffer(gl.ARRAY_BUFFER, rotVertexTextBuffer);
			gl.vertexAttribPointer(gl.ShaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

			//prepare texture buffer for drawing
			gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
			gl.vertexAttribPointer(gl.ShaderProgram.vertexTextureAttribute, 2, gl.FLOAT, false, 0, 0);
			gl.activeTexture(gl.TEXTURE0);
			gl.bindTexture(gl.TEXTURE_2D, gl.fntTexture);
			gl.uniform1i(gl.ShaderProgram.shaderSamplerUniform, 0);

			//handle rotation
			mvPushMatrix();
			mat4.rotate(mvMatrix, degToRad(refangle), [1, 0, 0]);
			mat4.rotate(mvMatrix, degToRad(angle), [0, 0, 1]);

			setMatrixUniforms(gl);

			gl.drawArrays(gl.TRIANGLE_STRIP, i*4, textposNum);

			//restore the model view matrix
			mvPopMatrix();
		}
	}

	function initBuffers(gl) {
		//position buffer
		vertexPositionBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

		//text buffer
		vertexTextBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textCoords), gl.STATIC_DRAW);

		//rotated text buffer
		rotVertexTextBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, rotVertexTextBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(rottextCoords), gl.STATIC_DRAW);

		//font texture buffer
		vertexTextureBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);

		//black texture buffer
		blackTextureBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, blackTextureBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(blacktextureCoords), gl.STATIC_DRAW);
	}

	function releaseBuffers() {
		gl.deleteBuffer(vertexPositionBuffer);
		gl.deleteBuffer(vertexTextureBuffer);
		gl.deleteBuffer(blackTextureBuffer);
		gl.deleteBuffer(vertexTextBuffer);
		gl.deleteBuffer(rotVertexTextBuffer);
	}

	function init(startingDistance, rotSpeed) {
		dist = startingDistance;
		rotationSpeed = rotSpeed;
	}

	function Rotate() {
		if(0 == pending_move) {
			if(0 == reflection%360)
				rotation += -360/vertexNum;
			else
				rotation -= -360/vertexNum;
		}
	}

	function Reflect() {
		if(0 == pending_move) {
			reflection += 180;
		}
	}

	function isPendingMove() {
		return pending_move;
	}

	function Animate(elapsedTime) {
		pending_move = 0;
		if((angle > rotation) && (angle - rotation > 1)) {
			angle -= rotationSpeed * elapsedTime / 1000.0;
			pending_move = 1
		}
		else if((angle < rotation) && ( rotation - angle > 1)) {
			angle += rotationSpeed * elapsedTime / 1000.0;
			pending_move = 1
		}

		if(refangle < reflection) {
			refangle += rotationSpeed * elapsedTime / 1000.0;
			pending_move = 1;
		}
	}

	function setVertexNum(num) {
		vertexNum = num;
	}

	function addTextureCoords(coords) {
		textureCoords = textureCoords.concat(coords);
	}

	return {
		init : init,
		vertices : vertices,
		textCoords : textCoords,
		rottextCoords : rottextCoords,
		blacktextureCoords : blacktextureCoords,
		initBuffers : initBuffers,
		releaseBuffers : releaseBuffers,
		setCamera : setCamera,
		setVertexNum : setVertexNum,
		addTextureCoords : addTextureCoords,
		Draw : Draw,
		Animate : Animate,
		isPendingMove : isPendingMove,
		Rotate : Rotate,
		Reflect : Reflect
	}
};


var Letters = new function() {
	var pos = new Array();
	var space = 0.0082;
	var letterw = 0.023;
	var letterh_begin = 0.9;
	var letterh_end = 0.66;
	
	function init() {
		pos['0'] = [letterw, letterh_begin, 0, letterh_begin, letterw, letterh_end, 0, letterh_end];
		pos['1'] = [letterw*2 + space, letterh_begin, letterw + space, letterh_begin,  letterw*2 + space, letterh_end,  letterw + space, letterh_end];
		pos['2'] = [letterw*3 + 2*space, letterh_begin, letterw*2 + 2*space, letterh_begin, letterw*3 + 2*space, letterh_end, letterw*2 + 2*space, letterh_end];
		pos['3'] = [letterw*4 + 3*space, letterh_begin, letterw*3 + 3*space, letterh_begin, letterw*4 + 3*space, letterh_end, letterw*3 + 3*space, 0.65];
		pos['4'] = [letterw*5 + 4*space, letterh_begin, letterw*4 + 4*space, letterh_begin, letterw*5 + 4*space, letterh_end, letterw*4 + 4*space, letterh_end];
		pos['5'] = [letterw*6 + 5*space, letterh_begin, letterw*5 + 5*space, letterh_begin, letterw*6 + 5*space, letterh_end, letterw*5 + 5*space, letterh_end];
		pos['6'] = [letterw*7 + 6*space, letterh_begin, letterw*6 + 6*space, letterh_begin, letterw*7 + 6*space, letterh_end, letterw*6 + 6*space, letterh_end];
		pos['7'] = [letterw*8 + 7*space, letterh_begin, letterw*7 + 7*space, letterh_begin, letterw*8 + 7*space, letterh_end, letterw*7 + 7*space, letterh_end];
		pos['8'] = [letterw*9 + 8*space, letterh_begin, letterw*8 + 8*space, letterh_begin, letterw*9 + 8*space, letterh_end, letterw*8 + 8*space, letterh_end];
		pos['9'] = [letterw*10 + 9*space, letterh_begin, letterw*9 + 9*space, letterh_begin, letterw*10 + 9*space, letterh_end, letterw*9 + 9*space, letterh_end];
	}	

	return {
		init : init,
		pos : pos
	};
}();


