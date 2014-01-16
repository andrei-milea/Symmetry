var Plotting = function() {
	var _scene = null;
	var _axes = null;
	var _points = [];
	var _is3d;
	var webgl_context;

	var prev_mouse_pt = [];

	function setGlContext(context) {
		webgl_context = context;
	}

	function clear() {
		_points = [];
		_axes = null;
		if(_scene !== null) {
			_scene.clearScene();
		}
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

		_scene.setGl(webgl_context.getGl());
		_scene.addModel(_axes);
		_scene.anim_loop();

		//initialize mouse position
		prev_mouse_pt[0] = 0;
		prev_mouse_pt[1] = 0;
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

	function addSurface(points) {
		surface = new Surface();
		surface.setPoints(points);
		_scene.addModel(surface);
	}

	function trackmouse(evt) {
		if(evt.which == 1) {
			//compute rotation axis
			var main_canvas = evt.target;
			var vec = vec3.create();
			vec[0] = - (prev_mouse_pt[1] - (evt.clientY / main_canvas.clientHeight));
			vec[1] = - (prev_mouse_pt[0] - (evt.clientX / main_canvas.clientWidth));
			vec[2] = 0;
			prev_mouse_pt[0] = (evt.clientX / main_canvas.clientWidth);
			prev_mouse_pt[1] = (evt.clientY / main_canvas.clientHeight);
			rotateScene(vec, vec3.length(vec));
		}
	}


	function highlightPlot(no) {
	}

	return {
		setGlContext : setGlContext,
		highlightPlot : highlightPlot,
		addCurve : addCurve,
		addSurface : addSurface,
		addAxes : addAxes,
		clear : clear,
		toggleCameraRotation : toggleCameraRotation,
		rotateScene : rotateScene,
		setZoom : setZoom,
		trackmouse : trackmouse
	}
};

