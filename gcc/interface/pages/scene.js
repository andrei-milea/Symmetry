var Scene = function() {
	this.scene_graph = new Array();
	this.animLastTime = 0;
	this.mvMatrix = mat4.create();
	this.pMatrix = mat4.create();
	this.gl = null;

	this.rotate = false;
	this.angle = 0.0;
	this.rotationSpeed = 10;

	this.zdist = -9.0;

	this.setDefaultCamera = function() {
		mat4.perspective(45, 1, 0.1, 100.0, this.pMatrix);
		mat4.identity(this.mvMatrix);
		mat4.translate(this.mvMatrix, [0.0, 0.0, this.zdist]);
	}

	this.toggleCameraRotation = function() {
		if(this.rotate === true)
			this.stopCameraRotation();
		else
			this.rotateCamera();
	}

	this.rotateScene = function(direction, length) {
		mat4.rotate(this.mvMatrix, this.degToRad(1), direction);
	}

	this.rotateCamera = function() {
		this.rotate = true;	
	}

	this.setZoom = function(zoom) {
		this.zdist = zoom;
		var newMatrix = mat4.create();
		mat4.identity(newMatrix);
		mat4.translate(newMatrix, [0.0, 0.0, this.zdist]);
		this.mvMatrix[12] = newMatrix[12];
		this.mvMatrix[13] = newMatrix[13];
		this.mvMatrix[14] = newMatrix[14];
		this.mvMatrix[15] = newMatrix[15];
	}

	this.stopCameraRotation = function() {
		this.rotate = false;	
	}

	this.initViewport = function() {
		this.gl.viewport(0, 0, this.gl.drawingBufferWidth, this.gl.drawingBufferHeight);
		this.gl.clearColor(242, 242, 242, 250);
	}

	this.setGl = function(_gl) {
		this.gl = _gl;
		this.gl.scene = this;
	}

	this.addModel = function(model) {
		model.initBuffers(this.gl);
		this.scene_graph.push(model);
		this.setDefaultCamera();
	}

	this.clearScene = function() {
		cancelRequestAnimFrame(this.anim_loop);
		for(var obj in this.scene_graph)
			this.scene_graph[obj].releaseBuffers(this.gl);
		this.scene_graph = [];
		this.setDefaultCamera();
	}

	this.drawScene = function() {
		this.initViewport();
		for(var obj in this.scene_graph)	{
			this.scene_graph[obj].setCamera(this.mvMatrix, this.pMatrix);
			this.scene_graph[obj].draw(this.gl);
		}
	}

	this.degToRad = function(degrees) {
		return degrees * Math.PI / 180;
	}

	this.animateScene = function() {

		var timeNow = new Date().getTime();
		if (this.animLastTime != 0) {
			var elapsed = timeNow - this.animLastTime;
			for(var obj in this.scene_graph) {
				this.scene_graph[obj].animate(elapsed);
			}

			if(this.rotate === true) {
				this.setDefaultCamera();
				this.angle += this.rotationSpeed * elapsed / 1000.0;
				if(this.angle > 360.0)
					this.angle = 0.0
				mat4.rotate(this.mvMatrix, this.degToRad(angle), [0, 1, 0]);
			}
		}
		this.animLastTime = timeNow;
	}

	this.anim_loop = function() {
		requestAnimFrame(this.anim_loop.bind(this));
		this.drawScene();
		this.animateScene();
	}
}

