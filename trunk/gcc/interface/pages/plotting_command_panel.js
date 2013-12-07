
//command panel  logic for vector and matrix computations
var PlottingPanel = function () {
	function show() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "block";
	}

	function hide() {
        var plottingDiv = document.getElementById("plotting_div_id");
		plottingDiv.style.display = "none";
	}

	function submitFct() {
		var fct_area = document.getElementById("fct_area_id");
		var command_input_str = fct_area.value.trim();
		var request = "command=GET_FCT_PLOT";
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
		addPlot(get_points(result.substr(6)));
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
		s.setMinimum(-29);
		s.setMaximum(-1);
		s.setValue(-15);
		s.onchange = function () {
			Plotting.setZoom(s.getValue());
		}



		var main_canvas = document.getElementById("main_canvas");
		main_canvas.width = 700;
		main_canvas.height = 700;
		WebGlContext.initWebGL();
		Plotting.clear();
		Plotting.addAxes(false);
		Plotting.addCurve(points);
	}

	function get_points(points_str) {
		var points = [];
		points_pairs = points_str.split(";");

		for(var i=0; i < points_pairs.length - 1; i++) {
			pair = points_pairs[i].split(",");
			points.push([parseFloat(pair[0]), parseFloat(pair[1])]);
		}
		
		return points;
	}

	return {
		show : show,
		hide : hide,
		submitFct : submitFct
	};
}();


