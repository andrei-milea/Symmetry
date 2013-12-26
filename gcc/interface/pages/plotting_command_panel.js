
//command panel  logic for vector and matrix computations
var PlottingPanel = function () {
	var prev_mouse_pt = [];
	var isSurface = new Boolean();

	function show() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "block";
		//initialize mouse position
		prev_mouse_pt[0] = 0;
		prev_mouse_pt[1] = 0;
	}

	function hide() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "none";
	}

	function submitFct() {
		var fct_area = document.getElementById("fct_area_id");
		var command_input_str = fct_area.value.trim();
		var request = "command=GET_FNC_PLOT";
		if(0 === command_input_str.length) {
			alert("Please provide the function first.")
			return;
		}
		request += "param=" + command_input_str;
		var result = submitCommand(request);
		if(-1 != result.indexOf("Error")) {
			alert("error : " + result);
			return;
		}
		var points = get_points(result.substr(6));
		addPlot(points);
	}

	function addPlot(points) {
	var canvasDiv = document.getElementById("canvas_id");
		if(canvasDiv.style.display === "block") {
			canvasDiv.innerHTML = "<canvas id='main_canvas' class='scanvas' width='700' height='700'>Your browser doesn't support canvas tag. Please update to a recent version in order to take full advantage when viewing this page.</canvas>";
			WebGlContext.initWebGL();
			canvasDiv.style.display = "none";
		}
		canvasDiv.style.display = "block";

		var sliderTag = document.createElement("div");
		sliderTag.innerHTML = "<input class='slider-input' id='slider-input-2' name='slider-input-2'/>";
		sliderTag.setAttribute("class","slider");
		sliderTag.setAttribute("id","slider-2");

		var main_canvas = document.getElementById("main_canvas");
		main_canvas.parentNode.insertBefore(sliderTag, main_canvas.nextSibling);
		sliderTag.parentNode.insertBefore(document.createElement("br"), sliderTag.nextSibling);
		sliderTag.parentNode.insertBefore(document.createElement("br"), sliderTag.nextSibling);
		var s = new Slider(document.getElementById("slider-2"), document.getElementById("slider-input-2"), "vertical");
		
		var main_canvas = document.getElementById("main_canvas");
		main_canvas.width = 700;
		main_canvas.height = 700;
		WebGlContext.initWebGL();
		Plotting.clear();
		if(isSurface === true) {
			Plotting.addAxes(true);
			Plotting.addSurface(points);
			//add mouse tracking rotation
			var main_canvas = document.getElementById("main_canvas");
			main_canvas.addEventListener('mousemove', trackmouse);
			s.setMinimum(-50);
			s.setMaximum(-10);
			s.setValue(-30);
			s.onchange = function () {
				Plotting.setZoom(s.getValue());
			}
			Plotting.setZoom(s.getValue());
		}
		else {
			Plotting.addAxes(false);
			Plotting.addCurve(points);
			s.setMinimum(-30);
			s.setMaximum(-2);
			s.setValue(-15);
			s.onchange = function () {
				Plotting.setZoom(s.getValue());
			}
			Plotting.setZoom(s.getValue());
		}
	}

	function trackmouse(evt) {
		if(evt.which == 1) {
			//compute rotation axis
			var main_canvas = document.getElementById("main_canvas");
			var vec = vec3.create();
			vec[0] = - (prev_mouse_pt[1] - (evt.clientY / main_canvas.clientHeight));
			vec[1] = - (prev_mouse_pt[0] - (evt.clientX / main_canvas.clientWidth));
			vec[2] = 0;
			prev_mouse_pt[0] = (evt.clientX / main_canvas.clientWidth);
			prev_mouse_pt[1] = (evt.clientY / main_canvas.clientHeight);
			Plotting.rotateScene(vec, vec3.length(vec));
		}
	}

	function get_points(points_str) {
		var points = [];
		isSurface = false;
		points_pairs = points_str.split(";");

		pair_tst = points_pairs[0].split(",");
		if(pair_tst.length === 3)
			isSurface = true;
		if(isSurface) {
			for(var i=0; i < points_pairs.length - 1; i++) {
				pair = points_pairs[i].split(",");
				points.push([parseFloat(pair[0]), parseFloat(pair[1]), parseFloat(pair[2])]);
			}
		}
		else {
			for(var i=0; i < points_pairs.length - 1; i++) {
				pair = points_pairs[i].split(",");
				points.push([parseFloat(pair[0]), parseFloat(pair[1])]);
			}
		}
		
		return points;
	}

	return {
		show : show,
		hide : hide,
		submitFct : submitFct
	};
}();


