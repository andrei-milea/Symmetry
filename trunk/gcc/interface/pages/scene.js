var Scene = function() {
	var scene_graph = new Array();
	var animLastTime = 0;
	var mvMatrix = mat4.create();
	var pMatrix = mat4.create();

	var rotate = false;
	var angle = 0.0;
	var rotationSpeed = 10;

	var zdist = -9.0;

	function setDefaultCamera() {
		mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);
		mat4.identity(mvMatrix);
		mat4.translate(mvMatrix, [0.0, 0.0, zdist]);
	}

	function toggleCameraRotation() {
		if(rotate === true)
			stopCameraRotation();
		else
			rotateCamera();
	}

	function rotateScene(direction, length) {
		mat4.rotate(mvMatrix, degToRad(1), direction);
	}

	function rotateCamera() {
		rotate = true;	
	}

	function setZoom(zoom) {
		zdist = zoom;
		setDefaultCamera();
	}

	function stopCameraRotation() {
		rotate = false;	
	}

	function initViewport() {
		gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
		//gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
		gl.clearColor(242, 242, 242, 250);
	}

	function setGl(_gl) {
		gl = _gl;
	}

	function addModel(model) {
		model.initBuffers(gl);
		scene_graph.push(model);
		setDefaultCamera();
	}

	function clearScene() {
		cancelRequestAnimFrame(anim_loop);
		for(var obj in scene_graph)
			scene_graph[obj].releaseBuffers();
		scene_graph = [];
		setDefaultCamera();
	}

	function drawScene() {
		initViewport();
		for(var obj in scene_graph)	{
			scene_graph[obj].setCamera(mvMatrix, pMatrix);
			scene_graph[obj].draw(gl);
		}
	}

	function degToRad(degrees) {
		return degrees * Math.PI / 180;
	}

	function animateScene() {

		var timeNow = new Date().getTime();
		if (animLastTime != 0) {
			var elapsed = timeNow - animLastTime;
			for(var obj in scene_graph) {
				scene_graph[obj].animate(elapsed);
			}

			if(rotate === true) {
				setDefaultCamera();
				angle += rotationSpeed * elapsed / 1000.0;
				if(angle > 360.0)
					angle = 0.0
				mat4.rotate(mvMatrix, degToRad(angle), [0, 1, 0]);
			}
		}
		animLastTime = timeNow;
	}

	function anim_loop() {
		requestAnimFrame(anim_loop);
		drawScene();
		animateScene();
	}
	
	return {
		addModel : addModel,
		anim_loop : anim_loop,
		setGl : setGl,
		clearScene : clearScene,
		rotateCamera : rotateCamera,
		rotateScene : rotateScene,
		toggleCameraRotation : toggleCameraRotation,
		setZoom : setZoom
	}

};
