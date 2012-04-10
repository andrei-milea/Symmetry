
var letters_pos = new Array();
var space = 0.0082;
var letterw = 0.023;
var letterh_begin = 0.9;
var letterh_end = 0.66;
letters_pos['0'] = [letterw, letterh_begin, 0, letterh_begin, letterw, letterh_end, 0, letterh_end];
letters_pos['1'] = [letterw*2 + space, letterh_begin, letterw + space, letterh_begin,  letterw*2 + space, letterh_end,  letterw + space, letterh_end];
letters_pos['2'] = [letterw*3 + 2*space, letterh_begin, letterw*2 + 2*space, letterh_begin, letterw*3 + 2*space, letterh_end, letterw*2 + 2*space, letterh_end];
letters_pos['3'] = [letterw*4 + 3*space, letterh_begin, letterw*3 + 3*space, letterh_begin, letterw*4 + 3*space, letterh_end, letterw*3 + 3*space, 0.65];
letters_pos['4'] = [letterw*5 + 4*space, letterh_begin, letterw*4 + 4*space, letterh_begin, letterw*5 + 4*space, letterh_end, letterw*4 + 4*space, letterh_end];
letters_pos['5'] = [letterw*6 + 5*space, letterh_begin, letterw*5 + 5*space, letterh_begin, letterw*6 + 5*space, letterh_end, letterw*5 + 5*space, letterh_end];
letters_pos['6'] = [letterw*7 + 6*space, letterh_begin, letterw*6 + 6*space, letterh_begin, letterw*7 + 6*space, letterh_end, letterw*6 + 6*space, letterh_end];
letters_pos['7'] = [letterw*8 + 7*space, letterh_begin, letterw*7 + 7*space, letterh_begin, letterw*8 + 7*space, letterh_end, letterw*7 + 7*space, letterh_end];
letters_pos['8'] = [letterw*9 + 8*space, letterh_begin, letterw*8 + 8*space, letterh_begin, letterw*9 + 8*space, letterh_end, letterw*8 + 8*space, letterh_end];
letters_pos['9'] = [letterw*10 + 9*space, letterh_begin, letterw*9 + 9*space, letterh_begin, letterw*10 + 9*space, letterh_end, letterw*9 + 9*space, letterh_end];



var WebGlContext = function()
{

var gl,
    shaderProgram,
    vertexPositionBuffer,
	vertexTextureBuffer,
	blackTextureBuffer,
	vertexTextBuffer,
	rotVertexTextBuffer,
    modelViewMatrix = mat4.create(),
    projectionMatrix = mat4.create(),
	rotation = 0,
	reflection = 0,
	pending_move = 0,
	mvMatrixStack = [],
	objects = [],
	animLastTime = 0,
	fntTexture,
	blackTexture;


////////////////////////////////////////////////////////////////
///////////////////////private functions////////////////////////
////////////////////////////////////////////////////////////////

function mvPushMatrix() 
{
	var copy = mat4.create();
	mat4.set(modelViewMatrix, copy);
	mvMatrixStack.push(copy);
}

function mvPopMatrix() 
{
	if (mvMatrixStack.length == 0) 
	{
		throw "Invalid popMatrix!";
	}
	modelViewMatrix = mvMatrixStack.pop();
}

function degToRad(degrees)
{
	return degrees * Math.PI / 180;
}

function buildFontTexture()
{
	fntTexture = gl.createTexture();
	var context2D = document.getElementById('textCanvas').getContext('2d');	
	context2D.font = 'normal 21px Times New Roman';
	context2D.fillStyle = 'rgba(255,255,255,2)';
	context2D.fillRect(0,0, 512, 64);
	context2D.lineWidth = 2;
	context2D.strokeStyle = 'rgba(0,0,0,255)';
	context2D.textAlign = 'left';
	context2D.textBaseline = 'middle';

	context2D.save();
  
	//context2D.clearRect ( 0 , 0 , 512 ,64);
	//context2D.fillRect(0, 0, 512, 64);

	context2D.fillStyle = 'rgba(252, 255, 255, 255)';
	context2D.strokeText("0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p r s t u v q x y z", 0, 15);
	context2D.strokeText("A B C D E F G H I J K L M N O P R S T U V Q X Y Z", 0, 40);
	context2D.fillStyle = 'rgba(80, 80, 80, 255)';
	context2D.fillText("0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p r s t u v q x y z", 0, 15);
	context2D.fillText("A B C D E F G H I J K L M N O P R S T U V Q X Y Z", 0, 40);

	context2D.fillStyle = 'rgba(0, 0, 0, 255)';
	context2D.fillRect(480, 50, 32, 14);

	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, fntTexture);
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, context2D.canvas);
	//canvas size must be power of 2
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);


	gl.bindTexture(gl.TEXTURE_2D, fntTexture);

	context2D.restore();
}

function buildBlackTexture()
{
	blackTexture = gl.createTexture();
	var context2D = document.getElementById('textCanvas').getContext('2d');	
	context2D.fillStyle = 'rgba(0,0,0,255)';
	context2D.fillRect(0,0, 512, 64);

	context2D.save();

	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, blackTexture);
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, context2D.canvas);
	//canvas size must be power of 2
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);


	gl.bindTexture(gl.TEXTURE_2D, blackTexture);

	context2D.restore();
}

function getShader(id) 
{
    var shaderScript = document.getElementById(id);
    if (!shaderScript) 
    {
        return null;
    }
 
    var str = "";
    var k = shaderScript.firstChild;
    while (k) 
    {
      if (k.nodeType == 3) 
      {
        str += k.textContent;
      }
      k = k.nextSibling;
    }
 
    var shader;
    if (shaderScript.type == "x-shader/x-fragment") 
    {
        shader = gl.createShader(gl.FRAGMENT_SHADER);
    } 
    else if (shaderScript.type == "x-shader/x-vertex") 
    {
        shader = gl.createShader(gl.VERTEX_SHADER);
    } 
    else
    {
      return null;
    }
 
    gl.shaderSource(shader, str);
    gl.compileShader(shader);
 
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) 
    {
        alert(gl.getShaderInfoLog(shader));
        return null;
    }
 
    return shader;
}

function initShaders()
{
    var fragmentShader = getShader("shader-fs");
    var vertexShader = getShader("shader-vs");
 
    shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);
 
    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) 
    {
        alert("Could not initialise shaders");
    }
 
    gl.useProgram(shaderProgram);
 
    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

	shaderProgram.vertexTextureAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
	gl.enableVertexAttribArray(shaderProgram.vertexTextureAttribute);

    shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
    shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
	shaderProgram.shaderSamplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
}

function clearScene()
{
        gl.clearColor(1, 1, 1, 1);
        gl.clearDepth(1.0);
        gl.enable(gl.DEPTH_TEST);
        gl.depthFunc(gl.LEQUAL);
}

function setMatrixUniforms()
{
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, projectionMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, modelViewMatrix);
}

function initBuffers(polygon)
{
	//position buffer
    vertexPositionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(polygon.vertices), gl.STATIC_DRAW);

	//text buffer
	vertexTextBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(polygon.textCoords), gl.STATIC_DRAW);

	//rotated text buffer
	rotVertexTextBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, rotVertexTextBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(polygon.rottextCoords), gl.STATIC_DRAW);

	//font texture buffer
	vertexTextureBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(polygon.textureCoords), gl.STATIC_DRAW);

	//black texture buffer
	blackTextureBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, blackTextureBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(polygon.blacktextureCoords), gl.STATIC_DRAW);

	vertexPositionBuffer.vertexNum = polygon.vertexNum;
}

function drawScene()
{
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

	mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, projectionMatrix);
	mat4.identity(modelViewMatrix);
	mat4.translate(modelViewMatrix, [0.0, 0.0, -7.0]);

	for(var obj in objects)
	{
		objects[obj].Draw();
	}
}

function DrawPolygon(polygon)
{
	//prepare position buffer for drawing
	gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, polygon.vertexSize, gl.FLOAT, false, 0, 0);

	//handle rotation
	mvPushMatrix();
	mat4.rotate(modelViewMatrix, degToRad(polygon.refangle), [1, 0, 0]);
	mat4.rotate(modelViewMatrix, degToRad(polygon.angle), [0, 0, 1]);

	//prepare texture buffer for drawing
	gl.bindBuffer(gl.ARRAY_BUFFER, blackTextureBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexTextureAttribute, polygon.textureposSize, gl.FLOAT, false, 0, 0);
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, blackTexture);
	gl.uniform1i(shaderProgram.shaderSamplerUniform, 0);

	setMatrixUniforms();
	gl.drawArrays(gl.LINE_LOOP, 0, polygon.vertexNum);

	//restore the model view matrix
	mvPopMatrix();
}

function DrawPolygonText(polygon)
{

	for(var i = 0; i < polygon.vertexNum; i++)
	{
		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextBuffer);
		gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, polygon.textposSize, gl.FLOAT, false, 0, 0);

		//prepare texture buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
		gl.vertexAttribPointer(shaderProgram.vertexTextureAttribute, polygon.textureposSize, gl.FLOAT, false, 0, 0);
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, fntTexture);
		gl.uniform1i(shaderProgram.shaderSamplerUniform, 0);

		//handle rotation
		mvPushMatrix();
		//mat4.rotate(modelViewMatrix, degToRad(rotation), [0, 0, 1]);


		setMatrixUniforms();

		gl.drawArrays(gl.TRIANGLE_STRIP, i*4, polygon.textposNum);

		//restore the model view matrix
		mvPopMatrix();
	}
	//draw rotated text
	for(var i = 0; i < polygon.vertexNum; i++)
	{
		//prepare position buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, rotVertexTextBuffer);
		gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, polygon.textposSize, gl.FLOAT, false, 0, 0);

		//prepare texture buffer for drawing
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexTextureBuffer);
		gl.vertexAttribPointer(shaderProgram.vertexTextureAttribute, polygon.textureposSize, gl.FLOAT, false, 0, 0);
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, fntTexture);
		gl.uniform1i(shaderProgram.shaderSamplerUniform, 0);

		//handle rotation
		mvPushMatrix();
		mat4.rotate(modelViewMatrix, degToRad(polygon.refangle), [1, 0, 0]);
		mat4.rotate(modelViewMatrix, degToRad(polygon.angle), [0, 0, 1]);


		setMatrixUniforms();

		gl.drawArrays(gl.TRIANGLE_STRIP, i*4, polygon.textposNum);

		//restore the model view matrix
		mvPopMatrix();
	}
}

//////////////////////////////////////////////////////
/////////////////////Polygon class////////////////////
//////////////////////////////////////////////////////
function Polygon(startingDistance, rotationSpeed)
{
	this.angle = 0;
	this.refangle = 0;
	this.dist = startingDistance;
	this.rotationSpeed = rotationSpeed;
}

Polygon.prototype.Draw = function()
{
//	mvPushMatrix();

	//move to the object's position
//	mat4.rotate(modelViewMatrix, degToRad(this.angle), [0.0, 1.0, 0.0]);
//	mat4.translate(modelViewMatrix, [this.dist, 0.0, 0.0]);

	//rotate back so that the object is facing the viewer
//	mat4.rotate(modelViewMatrix, degToRad(-this.angle), [0.0, 1.0, 0.0]);

	DrawPolygon(this);
	DrawPolygonText(this);

//	mvPopMatrix();
};


Polygon.prototype.animate = function(elapsedTime)
{
	pending_move = 0;
	if((this.angle > rotation) && (this.angle - rotation > 1))
	{
		this.angle -= this.rotationSpeed * elapsedTime / 1000.0;
		pending_move = 1
	}
	else if((this.angle < rotation) && ( rotation - this.angle > 1))
	{
		this.angle += this.rotationSpeed * elapsedTime / 1000.0;
		pending_move = 1
	}

	if(this.refangle < reflection)
	{
		this.refangle += this.rotationSpeed * elapsedTime / 1000.0;
		pending_move = 1;
	}
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


function animate()
{
	var timeNow = new Date().getTime();
	if (animLastTime != 0)
	{
		var elapsed = timeNow - animLastTime;
		for(var obj in objects)
		{
			objects[obj].animate(elapsed);
		}
	}
	animLastTime = timeNow;
}

function tick() 
{
	requestAnimFrame(tick);
	drawScene();
	animate();
}

////////////////////////////////////////////////////////////////
///////////////////////public functions/////////////////////////
////////////////////////////////////////////////////////////////
return  {
    initWebGL: function()   {
        var canvas = document.getElementById("main_canvas");
        try 
        {
			gl = WebGLUtils.setupWebGL(canvas);
			if(null != gl)
			{
				gl.viewportWidth = canvas.width;
				gl.viewportHeight = canvas.height;
				if (!gl) 
				{
					alert("Could not initialise WebGL, please update your browser!");
				}
				initShaders();
				clearScene();
				buildFontTexture();
				buildBlackTexture();
				tick();	
			}
         }
         catch(e)
         {
            document.writeln(e.name + ': ' + e.message);
         }
            
    },

	AddPolygonToScene: function(size)	{
		if(size < 3 || size > 9)
			return;
		var newpolygon = new Polygon(0, 50);

		newpolygon.vertices = [];
		newpolygon.textCoords = [];
		newpolygon.rottextCoords = [];
		newpolygon.textureCoords = [];
		newpolygon.blacktextureCoords = [];
		for(i = 1; i <= size; i++)
		{
			var x = 2.3 * Math.cos(2 * Math.PI * i / size);
			var y = 2.3 * Math.sin(2 * Math.PI * i / size);
			newpolygon.vertices.push(x);		//x coordintate
			newpolygon.vertices.push(y);		//y coordinate
			newpolygon.vertices.push(0);		//z coordinate
			var letter_weight = 0.152;
			var letter_height = 0.21;
			if(i < 10)
			{
				var rotx = x * 0.8;
				var roty = y * 0.8;
				x = x * 1.1;
				y = y * 1.1;
				newpolygon.textCoords.push(x + letter_weight/2);
				newpolygon.textCoords.push(y + letter_height/2);
				newpolygon.textCoords.push(0);

				newpolygon.textCoords.push(x - letter_weight/2);
				newpolygon.textCoords.push(y + letter_height/2);
				newpolygon.textCoords.push(0);

				newpolygon.textCoords.push(x + letter_weight/2);
				newpolygon.textCoords.push(y - letter_height/2);
				newpolygon.textCoords.push(0);

				newpolygon.textCoords.push(x-letter_weight/2);
				newpolygon.textCoords.push(y - letter_height/2);
				newpolygon.textCoords.push(0);

				newpolygon.rottextCoords.push(rotx + letter_weight/2);
				newpolygon.rottextCoords.push(roty + letter_height/2);
				newpolygon.rottextCoords.push(0);

				newpolygon.rottextCoords.push(rotx - letter_weight/2);
				newpolygon.rottextCoords.push(roty + letter_height/2);
				newpolygon.rottextCoords.push(0);

				newpolygon.rottextCoords.push(rotx + letter_weight/2);
				newpolygon.rottextCoords.push(roty - letter_height/2);
				newpolygon.rottextCoords.push(0);

				newpolygon.rottextCoords.push(rotx-letter_weight/2);
				newpolygon.rottextCoords.push(roty - letter_height/2);
				newpolygon.rottextCoords.push(0);

				newpolygon.textureCoords = newpolygon.textureCoords.concat(letters_pos[size - i + 1]);
				newpolygon.blacktextureCoords.push(1,1);
			}
		}


		newpolygon.vertexSize = 3;
		newpolygon.vertexNum = size;

		newpolygon.textposNum = 4;
		newpolygon.textposSize = 3;

		newpolygon.textureposNum = 4;
		newpolygon.textureposSize = 2;

		initBuffers(newpolygon);
		objects.push(newpolygon);
	},

	RotatePolygon: function()	{
		if(0 == pending_move)
		{
			if(0 == reflection%360)
				rotation += -360/vertexPositionBuffer.vertexNum;
			else
				rotation -= -360/vertexPositionBuffer.vertexNum;
		}
	},
	
	ReflectPolygon: function()	{
		if(0 == pending_move)
			reflection += 180;
	},

	isPendingMove: function()	{
		return pending_move;
	}


};



}();
