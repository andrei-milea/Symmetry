var WebGlContext = function() {
	var gl,
		shaderProgram;

	function buildFontTexture() {
		gl.fntTexture = gl.createTexture();
		var context2D = document.getElementById('textCanvas').getContext('2d');	
		context2D.font = 'normal 21px Times New Roman';
		context2D.fillStyle = 'rgba(255,255,255,2)';
		context2D.fillRect(0,0, 512, 64);
		context2D.lineWidth = 2;
		context2D.strokeStyle = 'rgba(0,0,0,255)';
		context2D.textAlign = 'left';
		context2D.textBaseline = 'middle';

		context2D.save();
	  
		context2D.fillStyle = 'rgba(252, 255, 255, 255)';
		context2D.strokeText("0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p r s t u v q x y z", 0, 15);
		context2D.strokeText("A B C D E F G H I J K L M N O P R S T U V Q X Y Z", 0, 40);
		context2D.fillStyle = 'rgba(80, 80, 80, 255)';
		context2D.fillText("0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p r s t u v q x y z", 0, 15);
		context2D.fillText("A B C D E F G H I J K L M N O P R S T U V Q X Y Z", 0, 40);

		context2D.fillStyle = 'rgba(0, 0, 0, 255)';
		context2D.fillRect(480, 50, 32, 14);

		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, gl.fntTexture);
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, context2D.canvas);
		//canvas size must be power of 2
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);

		gl.bindTexture(gl.TEXTURE_2D, gl.fntTexture);

		context2D.restore();
	}

	function buildBlackTexture() {
		gl.blackTexture = gl.createTexture();
		var context2D = document.getElementById('textCanvas').getContext('2d');	
		context2D.fillStyle = 'rgba(0,0,0,255)';
		context2D.fillRect(0,0, 512, 64);

		context2D.save();

		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, gl.blackTexture);
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, context2D.canvas);
		//canvas size must be power of 2
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);

		gl.bindTexture(gl.TEXTURE_2D, gl.blackTexture);

		context2D.restore();
	}

	function getShader(id) {
		var shaderScript = document.getElementById(id);
		if(!shaderScript) {
			return null;
		}
	 
		var str = "";
		var k = shaderScript.firstChild;
		while(k) {
		  if (k.nodeType == 3) {
			str += k.textContent;
		  }
		  k = k.nextSibling;
		}
	 
		var shader;
		if(shaderScript.type == "x-shader/x-fragment") {
			shader = gl.createShader(gl.FRAGMENT_SHADER);
		} 
		else if(shaderScript.type == "x-shader/x-vertex") {
			shader = gl.createShader(gl.VERTEX_SHADER);
		} 
		else {
		  return null;
		}
	 
		gl.shaderSource(shader, str);
		gl.compileShader(shader);
	 
		if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
			alert(gl.getShaderInfoLog(shader));
			return null;
		}
	 
		return shader;
	}

	function initShaders() {
		var fragmentShader = getShader("shader-fs");
		var vertexShader = getShader("shader-vs");
	 
		shaderProgram = gl.createProgram();
		gl.attachShader(shaderProgram, vertexShader);
		gl.attachShader(shaderProgram, fragmentShader);
		gl.linkProgram(shaderProgram);
	 
		if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
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

	function clearContext() {
			gl.clearColor(1, 1, 1, 1);
			gl.clearDepth(1.0);
			gl.enable(gl.DEPTH_TEST);
			gl.depthFunc(gl.LEQUAL);
	}

    function initWebGL() {
        var canvas = document.getElementById("main_canvas");
        try {
			gl = WebGLUtils.setupWebGL(canvas);
			if(null != gl) {
				gl.viewportWidth = canvas.width;
				gl.viewportHeight = canvas.height;
				if(!gl) {
					alert("Could not initialise WebGL, please update your browser!");
				}
				initShaders();
				clearContext();
				buildFontTexture();
				buildBlackTexture();
				gl.ShaderProgram = shaderProgram;
			}
         }
        catch(e) {
        	document.writeln(e.name + ': ' + e.message);
        }
    }

	function getGl() {
		return gl;
	}

	return {
		initWebGL : initWebGL,
		getGl : getGl
	};

}();
