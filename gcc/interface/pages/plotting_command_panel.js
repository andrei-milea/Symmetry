
//command panel  logic for vector and matrix computations
var PlottingPanel = function () {
	var isSurface = new Boolean();

	function show() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "block";
	}

	function hide() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "none";
	}

	function submitFct() {
		var div_id = "canvas_id";
		var canvas_id = "main_canvas";

		var fct_area = document.getElementById("fct_area_id");
		var command_input_str = fct_area.value.trim();
		var request = "command=GET_FNC_PLOT";
		if(0 === command_input_str.length) {
			alert("Please provide the function first.");
			return;
		}
		request += "param=" + command_input_str;
		var result = submitCommand(request);
		if(-1 !== result.indexOf("Error")) {
			alert("error : " + result);
			return;
		}
		var arg = Object();
		arg.points_str = result.substr(6);
		arg.div_id = div_id;
		arg.canvas_id = canvas_id;
		addPlot(arg);
	}

	function addPlot(arg) {
		var points = get_points(arg.points_str);
		var canvasDiv = document.getElementById(arg.div_id);
		canvasDiv.innerHTML = "<canvas id='" + arg.canvas_id + "' class='scanvas'></canvas>";
		canvasDiv.style.display = "block";

		var unique_id = Date.now();
		var sliderTag = document.createElement("div");
		sliderTag.innerHTML = "<input class='slider-input' id='slider-input-" + unique_id +"' />";
		sliderTag.setAttribute("class","slider");
		sliderTag.setAttribute("id","slider-" + unique_id);

		var main_canvas = document.getElementById(arg.canvas_id);
		main_canvas.parentNode.insertBefore(sliderTag, main_canvas.nextSibling);
		sliderTag.parentNode.insertBefore(document.createElement("br"), sliderTag.nextSibling);
		sliderTag.parentNode.insertBefore(document.createElement("br"), sliderTag.nextSibling);
		var slider = new Slider(document.getElementById("slider-" + unique_id),
			   	document.getElementById("slider-input-" + unique_id), "vertical");
		
		if(arg.canvas_id === "main_canvas") {
			main_canvas.style.width = "700px";
			main_canvas.style.height = "700px";
			main_canvas.width = 700;
			main_canvas.height = 700;
		}
		else {
			main_canvas.width = 150;
			main_canvas.height = 150;
		}
		var webgl_context = new WebGlContext();
		webgl_context.initWebGL(arg.canvas_id);
		var plotting = new Plotting();
		plotting.setGlContext(webgl_context);
		if(isSurface === true) {
			plotting.addAxes(true);
			plotting.addSurface(points);
			//add mouse tracking rotation
			main_canvas.addEventListener('mousemove', plotting.trackmouse);
			slider.setMinimum(-50);
			slider.setMaximum(-10);
			slider.setValue(-30);
			slider.onchange = function () {
				plotting.setZoom(slider.getValue());
			}
			slider.onchange();
			slider.recalculate();
		}
		else {
			plotting.addAxes(false);
			plotting.addCurve(points);
			slider.setMinimum(-30);
			slider.setMaximum(-2);
			slider.setValue(-15);
			slider.onchange = function () {
				plotting.setZoom(slider.getValue());
			}
			slider.onchange();
			slider.recalculate();
		}
	}

	function get_points(points_str) {
		var points = [];
		isSurface = false;
		var points_pairs = points_str.split(";");

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
		submitFct : submitFct,
		addPlot :addPlot 
	};
}();


