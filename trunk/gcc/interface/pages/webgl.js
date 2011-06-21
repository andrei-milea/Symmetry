
var WebGlContext = function()
{

var gl,
    shaderProgram,
    vertexPositionBuffer,
    modelViewMatrix,
    projectionMatrix;

//private functions

function initBuffers(shape)
{
    vertexPositionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, shape.getVerticesAsFloat32(), gl.STATIC_DRAW);
    vertexPositionBuffer.vertexSize = shape.getVertexSize();
    vertexPositionBuffer.vertexNum = shape.getVerticesNum();
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
 
    shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
    shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
}

function clearScene()
{
        gl.clearColor(0, 0, 0, 1);
        gl.clearDepth(1.0);
        gl.enable(gl.DEPTH_TEST);
        gl.depthFunc(gl.LEQUAL);
}

function drawLogo()
{
    var logo = Polygon;
    logo.load(3,3, [0.0,  1.0,  0.0, -1.0, -1.0,  0.0, 1.0, -1.0,  0.0]);
    initBuffers(logo);
}

//public functions
return  {
    initWebGL: function()   {
        var canvas = document.getElementById("3d_canvas");
        try 
        {
            gl = canvas.getContext("experimental-webgl");
            gl.viewport(0, 0, canvas.width, canvas.height);
            if (!gl) 
            {
                alert("Could not initialise WebGL, please update your browser!");
            }
            initShaders();
            clearScene();
            drawLogo();
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