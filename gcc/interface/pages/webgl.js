
var WebGlContext = function()
{

var gl,
    shaderProgram,
    vertexPositionBuffer,
	vertexColorBuffer,
    modelViewMatrix = mat4.create(),
    projectionMatrix = mat4.create(),
	rotation = 0,
	mvMatrixStack = [],
	animLastTime = 0;


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

	shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
    gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
 
    shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
    shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
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

function initBuffers(shape)
{
	//position buffer
    vertexPositionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(shape.vertices), gl.STATIC_DRAW);
    vertexPositionBuffer.vertexSize = shape.vertexSize;
    vertexPositionBuffer.vertexNum = shape.vertexNum;

	//color buffer
	vertexColorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexColorBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(shape.colors), gl.STATIC_DRAW);
    vertexColorBuffer.colorSize = shape.colorSize;
    vertexColorBuffer.colorNum = shape.colorNum;

}

function drawScene()
{
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

	mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, projectionMatrix);
	mat4.identity(modelViewMatrix);
	mat4.translate(modelViewMatrix, [0.0, 0.0, -7.0]);

	//prepare position buffer for drawing
	gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, vertexPositionBuffer.vertexSize, gl.FLOAT, false, 0, 0);

	//prepare color buffer for drawing
	gl.bindBuffer(gl.ARRAY_BUFFER, vertexColorBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, vertexColorBuffer.colorSize, gl.FLOAT, false, 0, 0);

	//handle rotation
	mvPushMatrix();
	mat4.rotate(modelViewMatrix, degToRad(rotation), [0, 0, 1]);


	setMatrixUniforms();
	gl.drawArrays(gl.LINE_LOOP, 0, vertexPositionBuffer.vertexNum);

	//restore the model view matrix
	mvPopMatrix();
}

function drawLogo()
{
	var shape = new Object;
	shape.vertices = [0.0,  1.0,  0.0,
					-1.0, -1.0,  0.0,
					 1.0, -1.0,  0.0];
	shape.vertexSize = 3;
	shape.vertexNum = 3;

	shape.colors = [0.0, 0.0, 0.0, 1.0,
					0.0, 0.0, 0.0, 1.0,
					0.0, 0.0, 0.0, 1.0];
	shape.colorSize = 4;
	shape.colorNum = 3;
    initBuffers(shape);
	drawScene();
}

function animate()
{
	var timeNow = new Date().getTime();
	if (animLastTime != 0)
	{
		var elapsed = timeNow - animLastTime;
		rotation += (90 * elapsed) / 1000.0;
	}
	animLastTime = timeNow;
}

function tick() 
{
	requestAnimFrame(tick);
	drawLogo();
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
				tick();	
			}
         }
         catch(e)
         {
            document.writeln(e.name + ': ' + e.message);
         }
            
    },

    drawShape: function(shape)  {
        this.clearScene();
        initBuffers(shape);
        //TODO
    }
};



}();
