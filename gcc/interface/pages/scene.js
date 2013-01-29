var Scene = function() {
	var scene_graph = new Array();
	var animLastTime = 0;
	var mvMatrix = mat4.create();
	var pMatrix = mat4.create();

	function setDefaultCamera() {
		mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);
		mat4.identity(mvMatrix);
		mat4.translate(mvMatrix, [0.0, 0.0, -7.0]);
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
	}

	function clearScene() {
		cancelRequestAnimFrame(anim_loop);
		for(var obj in scene_graph)
			scene_graph[obj].releaseBuffers();
		scene_graph = [];
	}

	function drawScene() {
		initViewport();
		setDefaultCamera();
		for(var obj in scene_graph)	{
			scene_graph[obj].setCamera(mvMatrix, pMatrix);
			scene_graph[obj].Draw(gl);
		}
	}

	function animateScene() {
		var timeNow = new Date().getTime();
		if (animLastTime != 0) {
			var elapsed = timeNow - animLastTime;
			for(var obj in scene_graph) {
				scene_graph[obj].Animate(elapsed);
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
		clearScene : clearScene
	}

};
