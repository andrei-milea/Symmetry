
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
		number++;

		var polyTable = document.getElementById("poly_table_id");
		var row = polyTable.getElementsByTagName("tr")[0];
		var coef_no = row.getElementsByTagName("td").length;
		if(coef_no < number) {
			for(var i = coef_no; i < number; i++) {
				var newcoef = row.insertCell(-1);
				newcoef.innerHTML = "<input type='text' id='entry" + i.toString() + "' size='5' maxlength='15'>";
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
		var insert_matrix_expr_div = document.getElementById("insert_matrix_expr_id");
		if(insert_matrix_expr_div.style.display === "none") {
			command_input_str="$\\begin{bmatrix}"; 
			var matTable = document.getElementById("mat_table_id");
			var rows = matTable.getElementsByTagName("tr");
			for(var i = 0; i < rows.length; i++) {
				var cols = rows[i].getElementsByTagName("td");
				if(i != 0)
					command_input_str+= "\\\\";
				for(var j = 0; j < cols.length; j++) {
					if(j != 0)
						command_input_str+= " & ";
					var val_str = document.getElementById("entry" + (i+1).toString() + (j+1).toString()).value;
					if(isNaN(val_str) || (val_str == "")) {
						window.alert("Invalid input. Please enter valid coefficients and constant terms!")
						return;
					}
					command_input_str += val_str;
				}
			}
			command_input_str+="\\end{bmatrix}$";
			var added_input_div = document.getElementById("added_input_id");
			added_input_div.innerHTML = "</br><b>The matrix you provided as input is:</b> </br></br>" + command_input_str + "</br></br>";
			added_input_div.style.display = "block";
			MainMenu.hide_input_box();
		}
		else {
			var mat_expr = document.getElementById("mat_expr_text_id");
			var added_input_div = document.getElementById("added_input_id");
			command_input_str = mat_expr.value;
			var result = submit_command('GET_MAT_EXPR');
			if(result.indexOf("$") === -1) {
				alert("Invalid input: " + result + ".Please enter valid (la)tex code for a linear combination.");
				return;
			}
			command_input_str = result;
			added_input_div.innerHTML = "</br><b>The matrix expression you provided as input is:</b> </br></br>" + mat_expr.value + "</br></br> <b>with the result: </b></br></br>" + result + "</br></br>";
			added_input_div.style.display = "block";
			MainMenu.hide_input_box();
			mat_expr_computed = false;
		}
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	function submit_command(command) {
		var request = "command=" + command;
		var _command_input_str = command_input_str.substr(1,command_input_str.length-1);
		if(0 === _command_input_str.length) {
			alert("Please provide the input first(matrix, vector, linear combination).")
			return;
		}
		request += "param=" + _command_input_str;
		if(command === 'GET_MAT_EXPR') {
			return submitCommand(request);
		}
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


