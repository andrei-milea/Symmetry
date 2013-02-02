var LinGeometry = function() {
	var _scene = null;
	var _axes = null;
	var _linear_equations = [];
	var _is3d;

	function clear() {
		_linear_equations = [];
		_axes = null;
	}

	function addAxes(is3d) {
		if(_scene !== null) {
			_scene.clearScene();
		}
		_scene = new Scene();
		_axes = new CoordAxes();

		if(is3d) {
			_axes.set3D();
		}
		_is3d = is3d;

		_scene.setZoom(-15);

		_scene.setGl(WebGlContext.getGl());
		_scene.addModel(_axes);
		_scene.anim_loop();
	}

	function toggleCameraRotation() {
		if(_is3d)
			_scene.toggleCameraRotation();
	}

	function zoom_in() {
		_scene.zoom_in();
	}

	function zoom_out() {
		_scene.zoom_out();
	}

	function add2DEquation(x, y, r) {
		lin_eq = new LinEq();
		lin_eq.set2DEquation(x, y, r);
		_linear_equations.push(lin_eq);
		_scene.addModel(lin_eq);
	}

	function add3DEquation(x, y, z, r) {
		lin_eq = new LinEq();
		lin_eq.set3DEquation(x, y, z, r);
		_linear_equations.push(lin_eq);
		_scene.addModel(lin_eq);
	}

	function highlightEquation(no) {
		var index = parseInt(no);
		for(var idx = 0; idx < _linear_equations.length; idx++)
			_linear_equations[idx].unhighlight();

		_linear_equations[index].highlight();
	}

	return {
		highlightEquation : highlightEquation,
		add2DEquation : add2DEquation,
		add3DEquation : add3DEquation,
		addAxes : addAxes,
		clear : clear,
		toggleCameraRotation : toggleCameraRotation,
		zoom_in : zoom_in,
		zoom_out : zoom_out
	}
}();

