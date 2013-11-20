
//command panel  logic for vector and matrix computations
var PolyPanel = function () {
	var mat_expr_computed = true;
	var command_input_str = "";

	function show() {
		var poly_command_panelDiv = document.getElementById("poly_panel");
        var polyDiv = document.getElementById("poly_div_id");
		poly_command_panelDiv.style.display = "block";
		polyDiv.style.display = "block";
	}

	function hide() {
		var poly_command_panelDiv = document.getElementById("poly_panel");
        var polyDiv = document.getElementById("poly_div_id");
		poly_command_panelDiv.style.display = "none";
		polyDiv.style.display = "none";
	}

	function degreeChanged(elem) {
		var number = parseInt(elem.value);
		if(number <= 0) {
			elem.value = 1;
			degreeChanged(elem);
			return;
		}
		if(number > 10) {
			elem.value = 10;
			degreeChanged(elem);
			return;
		}
		number++;

		var polyTable = document.getElementById("poly_table_id");
		var row = polyTable.getElementsByTagName("tr")[0];
		var coef_no = row.getElementsByTagName("td").length;
		if(coef_no < number) {
			for(var i = coef_no; i < number; i++) {
				var newcoef = row.insertCell(-1);
				newcoef.innerHTML = "<input type='text' id='entry" + (i+1).toString() + "' size='5' maxlength='15'>$x^" +
				   	i.toString() + "$";
			}
		}
		else if(coef_no > number) {
			var row = polyTable.getElementsByTagName("tr")[0];
			while(coef_no > number)
			{
				row.deleteCell(coef_no-1);
				coef_no--;
			}
		}
	}

	function polySelection(select) {
		if(select.value === "Single Variable Polynomial") {
			//TODO
		}
		else if(select.value === "Multivariable Polynomial") {
			//TODO
		}
	}

	function submitPoly() {
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

		for(var i=0; i < points_pairs.length; i++) {
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
		}
		main_view.innerHTML = "</br></br><b>" + result + "</b></br></br>";
		main_view.style.display = "block";
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	return {
		show : show,
		hide : hide,
		degreeChanged : degreeChanged,
		submitPoly : submitPoly,
		polySelection : polySelection,
		submit_command : submit_command
	};
}();


