
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
		var _tex_input_str = "$";
		command_input_str = "";
		var polyTable = document.getElementById("poly_table_id");
		var rows = polyTable.getElementsByTagName("tr");
		var cols = rows[0].getElementsByTagName("td");
		for(var j = 0; j < cols.length; j++) {
			if(j != 0) {
				_tex_input_str += " + ";
				command_input_str += ",";
			}
			var val_str = document.getElementById("entry" + (j+1).toString()).value;
			if(isNaN(val_str) || (val_str == "")) {
				window.alert("Invalid input. Please enter valid coefficients and constant terms!")
				return;
			}
			if(j === 0)
				_tex_input_str += val_str;
			else if(j == 1)
				_tex_input_str += val_str + " x";
			else
				_tex_input_str += val_str + " x^" + (j).toString();
	

			command_input_str += val_str;
		}
		_tex_input_str += "$";
		var added_input_div = document.getElementById("added_input_id4");
		added_input_div.innerHTML = "</br><b>The polynomial you provided as input is:</b> </br></br> $p(x) =$ " + 
							_tex_input_str + "</br></br>";
		added_input_div.style.display = "block";

		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
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

	function submit_command(command) {
		var request = "command=" + command;
		if(0 === command_input_str.length) {
			alert("Please provide the polynomial first.")
			return;
		}
		request += "param=" + command_input_str;
		var main_view = document.getElementById("main_view_id");
		var result = submitCommand(request);
		if(-1 != result.indexOf("Error")) {
			alert("error : " + result);
			return;
		}
		if(command === "GET_POLY_PLOT") {
			addPlot(get_points(result.substr(6)));
			return;
		}
		main_view.innerHTML = "</br></br><b>" + result + "</b></br></br>";
		main_view.style.display = "block";
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	return {
		show : show,
		hide : hide,
		submitFct : submitFct,
		submit_command : submit_command
	};
}();


