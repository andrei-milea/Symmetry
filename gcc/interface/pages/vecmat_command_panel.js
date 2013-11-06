
//command panel  logic for vector and matrix computations
var VecMatPanel = function () {
	var mat_expr_computed = true;
	var command_input_str = "";

	function show() {
        var vecmatDiv = document.getElementById("vecmat_div_id");
		vecmatDiv.style.display = "block";
	}

	function hide() {
        var vecmatDiv = document.getElementById("vecmat_div_id");
		vecmatDiv.style.display = "none";
	}

	function rows_num_changed(elem) {
		var number = parseInt(elem.value);
		if(number <= 0) {
			elem.value = 1;
			rows_num_changed(elem);
			return;
		}
		var matTable = document.getElementById("mat_table_id");
		var rowsnum = matTable.getElementsByTagName("tr").length;
		var colsnum = matTable.getElementsByTagName("tr")[0].getElementsByTagName("td").length;
		if(rowsnum < number) {
			var j = 0;
			while(rowsnum + j < number)
			{
				var newrow = matTable.insertRow(-1);
 
				for(var i = 1; i <= colsnum; i++)
				{	
					var newcol = newrow.insertCell(-1);
					newcol.innerHTML = "<input type='text' id='entry" + (rowsnum + j + 1).toString() + i.toString() +
					   	"' size='5' maxlength='15'>";
				}
				j++;
			}
		}
		else if(rowsnum > number) {
			var j = 0;
			var rows = matTable.getElementsByTagName("tr");
			while(number < rowsnum - j)
			{
				matTable.deleteRow(-1);
				j++;
			}
		}
	}

	function cols_num_changed(elem) {
		var number = parseInt(elem.value);
		if(number <= 0) {
			elem.value = 1;
			cols_num_changed(elem);
			return;
		}
		var matTable = document.getElementById("mat_table_id");
		var rows = matTable.getElementsByTagName("tr");
		var colsnum = rows[0].getElementsByTagName("td").length;
		if(colsnum - 1 < number) {
			for(var i = 0; i < rows.length; i++) {
				var j = 0;
				while(colsnum + j < number) {
					var newcol = rows[i].insertCell(-1);
					newcol.innerHTML = "<input type='text' id='entry" + (i+1).toString() + (colsnum + j + 1).toString() +
					   	"' size='5' maxlength='15'>";
					j++;
				}
			}
		}
		else if(colsnum > number) {
			for(var i = 0; i < rows.length; i++) {
				var j = 0;
				while(colsnum - j > number) {
					rows[i].deleteCell(colsnum - 1 - j);
					j++;
				}
			}
		}
	}

	function matrixSelection(select) {
		if(select.value === "Input a matrix") {
			var insert_matrix_div = document.getElementById("insert_matrix_id");
			var insert_matrix_expr_div = document.getElementById("insert_matrix_expr_id");
			insert_matrix_div.style.display = "block";
			insert_matrix_expr_div.style.display = "none";
		}
		else if(select.value === "Input a vector (column matrix)") {
			var insert_matrix_div = document.getElementById("insert_matrix_id");
			var insert_matrix_expr_div = document.getElementById("insert_matrix_expr_id");
			insert_matrix_div.style.display = "block";
			insert_matrix_expr_div.style.display = "none";
			var cols_number = document.getElementById("cols_number_id");
			cols_number.value = 1;
			cols_num_changed(cols_number);
		}
		else {//input a matrix expression
			var insert_matrix_div = document.getElementById("insert_matrix_id");
			var insert_matrix_expr_div = document.getElementById("insert_matrix_expr_id");
			insert_matrix_div.style.display = "none";
			insert_matrix_expr_div.style.display = "block";
		}

	}

	function submitMat() {
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
		else if(command === 'GET_NORM') {
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("error : " + result);
				return;
			}
			else {
				main_view.innerHTML = "<b>euclidean norm: " + result + "</b></br></br>";
				main_view.style.display = "block";
			}
		}
		else if(command === 'GET_MAT_DETERMINANT')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("error : " + result);
				return;
			}
			else {
				main_view.innerHTML = "<b>determinant and trace: " + result + "</b></br></br>";
				main_view.style.display = "block";
				MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
			}
		}
		else if(command === 'GET_MAT_INVERSE')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("error : " + result);
				return;
			}
			else {
				main_view.innerHTML = "</br><b>inverse matrix: " + result + "</b></br></br>";
				main_view.style.display = "block";
				MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
			}
		}
		else if(command === 'GET_MAT_RREF')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("Error: " + result);
				return;
			}
			else {
				main_view.innerHTML = "</br><b>row reduced echelon form: " + result + "</b></br></br>";
				main_view.style.display = "block";
				MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
			}
		}
		else if(command === 'GET_MAT_EIGENVALUES')
		{
			/*TODO
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("error : " + result);
				return;
			}
			else {
				main_view.innerHTML = "</br><b>Eigenvalues: " + result + "</b></br></br>";
				main_view.style.display = "block";
				MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
			}
			*/
		}
	}

	return {
		show : show,
		hide : hide,
		rows_num_changed : rows_num_changed,
		cols_num_changed : cols_num_changed,
		submitMat : submitMat,
		matrixSelection : matrixSelection,
		submit_command : submit_command
	};
}();


