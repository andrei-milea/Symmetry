var Plotting = function() {
	var _scene = null;
	var _axes = null;
	var _points = [];
	var _is3d;

	function clear() {
		_points = [];
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

		_scene.setGl(WebGlContext.getGl());
		_scene.addModel(_axes);
		_scene.setZoom(-15);
		_scene.anim_loop();
	}

	function toggleCameraRotation() {
		if(_is3d)
			_scene.toggleCameraRotation();
	}

	function rotateScene(direction, length) {
		if(_is3d)
			_scene.rotateScene(direction, length);
	}

	function setZoom(zoom) {
		_scene.setZoom(zoom);
	}

	function zoom_out() {
		_scene.zoom_out();
	}

	function addCurve(points) {
		curve = new Curve();
		curve.setPoints(points);
		_scene.addModel(curve);
	}

	function highlightPlot(no) {
	}

	return {
		highlightPlot : highlightPlot,
		addCurve : addCurve,
		addAxes : addAxes,
		clear : clear,
		toggleCameraRotation : toggleCameraRotation,
		rotateScene : rotateScene,
		setZoom : setZoom
	}
}();

