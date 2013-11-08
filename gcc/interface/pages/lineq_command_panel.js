
//command pannel for linear equations
var LinEqPanel = function () {
	var command_input_str = "";
	var sys_matrix;

	function show() {
		var lineqcommand_panelDiv = document.getElementById("lineq_commands_panel");
        var lineqDiv = document.getElementById("lineq_div_id");
		lineqcommand_panelDiv.style.display = "block";
		lineqDiv.style.display = "block";
	}

	function hide() {
		var lineqcommand_panelDiv = document.getElementById("lineq_commands_panel");
        var lineqDiv = document.getElementById("lineq_div_id");
		lineqcommand_panelDiv.style.display = "none";
		lineqDiv.style.display = "none";
	}

	function lineq_num_changed(elem) {
		var number = parseInt(elem.value);
		if(number <= 1) {
			elem.value = 2;
			lineq_num_changed(elem);
			return;
		}
		var lineqTable = document.getElementById("lineq_table_id");
		var rowsnum = lineqTable.getElementsByTagName("tr").length;
		var colsnum = lineqTable.getElementsByTagName("tr")[0].getElementsByTagName("td").length;
		if(rowsnum < number) {
			var j = 0;
			while(rowsnum + j < number) {
				var newrow = lineqTable.insertRow(-1);
 
				for(var i = 1; i < colsnum; i++) {	
					var newcol = newrow.insertCell(-1);
					newcol.innerHTML = "<input type='text' id='unknown" + (rowsnum + j + 1).toString() + i.toString() +
					   	"' size='5' maxlength='15'> $x_" + i.toString() + "$";
				}
				var newcol = newrow.insertCell(-1);
				newcol.innerHTML = "<input type='text' id='result" + (rowsnum + j + 1).toString() +
				   	"' size='5' maxlength='15'> $b_" + (rowsnum + j + 1).toString() + "$";
				newrow.appendChild(newcol);
				j++;
			}
		}
		else if(rowsnum > number) {
			var j = 0;
			var rows = lineqTable.getElementsByTagName("tr");
			while(number < rowsnum - j) {
				lineqTable.deleteRow(-1);
				j++;
			}
		}
	}

	function unknowns_num_changed(elem) {
		var number = parseInt(elem.value);
		if(number <= 1) {
			elem.value = 2;
			unknowns_num_changed(elem);
			return;
		}
		var lineqTable = document.getElementById("lineq_table_id");
		var rows = lineqTable.getElementsByTagName("tr");
		var colsnum = rows[0].getElementsByTagName("td").length;
		if(colsnum - 1 < number) {
			for(var i = 0; i < rows.length; i++) {
				var j = 0;
				while(colsnum + j - 1 < number) {
					var newcol = rows[i].insertCell(rows[i].getElementsByTagName("td").length - 1);
					newcol.innerHTML = "<input type='text' id='unknown" + (i+1).toString() + (colsnum + j).toString() +
					   	"' size='5' maxlength='15'> $x_" + (colsnum + j).toString() + "$";
					j++;
				}
			}
		}
		else if(colsnum > number)
		{
			for(var i = 0; i < rows.length; i++) {
				var j = 0;
				while(colsnum - j - 1 > number) {
					rows[i].deleteCell(colsnum - 2 - j);
					j++;
				}
			}
		}
	}

	function submitSystem() {
		var system_str="$\\begin{cases}"; 
		command_input_str="$\\begin{bmatrix}"; 
		var lineqTable = document.getElementById("lineq_table_id");
		var rows = lineqTable.getElementsByTagName("tr");
		var lineq_size = 0;

		//alloc dynamic array of arrays
		sys_matrix = new Array(rows.length);

		for(var i = 0; i < rows.length; i++) {
			var cols = rows[i].getElementsByTagName("td");
			lineq_size = cols.length - 1;
			sys_matrix[i] = new Array(cols.length);
			if(0 !== i)
				command_input_str+= "\\\\";
			for(var j = 0; j < cols.length - 1; j++) {
				if(j != 0) {
					system_str+= " + ";
					command_input_str+= " & ";
				}
				var val_str = document.getElementById("unknown" + (i+1).toString() + (j+1).toString()).value;
				if(isNaN(val_str) || (val_str == "")) {
					window.alert("Invalid input. Please enter valid coefficients and constant terms!")
					return;
				}
				system_str += val_str + "x_" + (j+1).toString();
				command_input_str += val_str;
				sys_matrix[i][j] = parseFloat(val_str);
			}

			system_str+= " = ";
			var res_str = document.getElementById("result" + (i+1).toString()).value;
			if(isNaN(res_str) || (res_str == "")) {
				window.alert("Invalid input. Please enter valid coefficients and constant terms!")
				return;
			}
			system_str += res_str;
			sys_matrix[i][cols.length - 1] = parseFloat(res_str);

			command_input_str+= " & ";
			command_input_str += document.getElementById("result" + (i+1).toString()).value;
			system_str+= "\\\\";
		}
		system_str+="\\end{cases}$";
		command_input_str+="\\end{bmatrix}$";

		var added_input_div = document.getElementById("added_input_id2");
		added_input_div.innerHTML = "</br><b>The linear system you provided as input is:</b> </br></br>" + system_str + "<br></br><b>with the associated matrix:</b></br></br>" + command_input_str + "</br></br>";
		added_input_div.style.display = "block";
		if(lineq_size < 4)
			addGeometry(sys_matrix);
		else
			removeGeometry();
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	function submit_command(command) {
		var request = "command=" + command;
		var _command_input_str = command_input_str.substr(1,command_input_str.length-1);
		if(0 === _command_input_str.length) {
			alert("Please provide the input linear system first.")
			return;
		}
		request += "param=" + _command_input_str;
		if(command === 'SOLVE_LINEQ_SYS' || command === 'APPROX_LINEQ_SYS' || command === 'SOLVEG_LINEQ_SYS') {
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("error : " + result);
				return;
			}
			main_view.innerHTML = "</br></br><b>vector solution: " + result + "</b></br></br>";
			main_view.style.display = "block";
			MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
		}
	}


	function addGeometry(sys_matrix) {
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
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);
		canvasDiv.insertBefore(document.createTextNode('Geometric Interpretation(right-hand coordinate system):'), main_canvas);
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);

		var toggleTag = document.createElement("input");
		toggleTag.setAttribute("type","button");
		toggleTag.setAttribute("value","Toggle Camera Rotation");
		toggleTag.setAttribute("onclick","LinGeometry.toggleCameraRotation()"); 

		var zoom_inTag = document.createElement("input");
		zoom_inTag.setAttribute("type","button");
		zoom_inTag.setAttribute("value","Zoom in");
		zoom_inTag.setAttribute("onclick","LinGeometry.zoom_in()"); 

		var zoom_outTag = document.createElement("input");
		zoom_outTag.setAttribute("type","button");
		zoom_outTag.setAttribute("value","Zoom out");
		zoom_outTag.setAttribute("onclick","LinGeometry.zoom_out()"); 


		canvasDiv.insertBefore(zoom_inTag, main_canvas);
		canvasDiv.insertBefore(zoom_outTag, main_canvas);
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);
		canvasDiv.insertBefore(toggleTag, main_canvas);
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);
		canvasDiv.insertBefore(document.createElement("br"), main_canvas);

		WebGlContext.initWebGL();
		LinGeometry.clear();
		if(sys_matrix[0].length === 4) {
			addGeometryRadioB(sys_matrix);
			LinGeometry.addAxes(true);

			for(var idx = 0; idx < sys_matrix.length; idx++)
				LinGeometry.add3DEquation(sys_matrix[idx][0], sys_matrix[idx][1], sys_matrix[idx][2], sys_matrix[idx][3]);

		}
		else {
			LinGeometry.addAxes(false);
			addGeometryRadioB(sys_matrix);

			for(var idx = 0; idx < sys_matrix.length; idx++)
				LinGeometry.add2DEquation(sys_matrix[idx][0], sys_matrix[idx][1], sys_matrix[idx][2]);
		}

		canvasDiv.appendChild(document.createElement("br"));
		canvasDiv.appendChild(document.createElement("br"));
	}

	function removeGeometry() {
		var canvasDiv = document.getElementById("canvas_id");
		if(canvasDiv.style.display === "block") {
			canvasDiv.innerHTML = "<canvas id='main_canvas' class='scanvas' width='700' height='700'>Your browser doesn't support canvas tag. Please update to a recent version in order to take full advantage when viewing this page.</canvas>";
			WebGlContext.initWebGL();
			canvasDiv.style.display = "none";
			LinGeometry.clear();
		}
	}

	function addGeometryRadioB(sys_matrix) {

		new_div = document.createElement("div");
		new_div.align = 'center';
		new_div.innerHTML = "Highlight a linear equation(in red): </br>";
		for(var i = 0; i < sys_matrix.length; i++) {
			var system_str = "$";
			var j = 0;
			for(j = 0; j < sys_matrix[i].length - 1; j++) {
				if(j != 0) {
					system_str+= " + ";
				}
				system_str += sys_matrix[i][j].toString() + "x_" + (j+1).toString();
			}
			system_str += " = ";
			system_str += sys_matrix[i][j].toString();
			system_str += "$";

			//add to page
			new_div.innerHTML += "<input type='radio' onclick='LinGeometry.highlightEquation(value)' name='group1' value='" + i.toString() + "'>" + system_str + "</br>";
		}

		var canvasDiv = document.getElementById("canvas_id");
		var main_canvas = document.getElementById("main_canvas");
		canvasDiv.insertBefore(new_div, main_canvas);
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}


	
	return {
		show : show,
		hide : hide,
		lineq_num_changed : lineq_num_changed,
		unknowns_num_changed : unknowns_num_changed,
		submitSystem : submitSystem,
		submit_command : submit_command
	};
}();


