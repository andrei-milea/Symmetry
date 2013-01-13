
//global function that submits a command to the symmetry server
//and returns its result -- used in all the componets
XMLHttpRequest.prototype.sendAsBin = function(datastr) {
	var ui8a = new Uint8Array(datastr.length);
	for (var i = 0; i < datastr.length; i++) {
			ui8a[i] = (datastr.charCodeAt(i) & 0xff);
	}
	this.send(ui8a.buffer);
}

function submitCommand (request) {
	var xmlhttp;
	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	} 

	var sessionkeyTag = document.getElementById("session_key_id");

	var _request = "id=" + sessionkeyTag.value + request;
	xmlhttp.open("POST", self.location.hostname, false);
	xmlhttp.setRequestHeader("Content-type", "text/plain; charset=US-ASCII");
	//xmlhttp.setRequestHeader("Content-length", _request.length);
	//xmlhttp.setRequestHeader("Connection", "close");
	xmlhttp.sendAsBin(_request);
	return xmlhttp.responseText;
}

var MainMenu = function () {
	var current_panel = null;
	var input_box_state = "hidden";

	function toggle_input_box() {
		if(input_box_state === "hidden")
			show_input_box();
		else
			hide_input_box();
	}

	function show_input_box() {
		input_box_state = "shown";
		var input_box_button = document.getElementById("inputbox_button");
		input_box_button.value='Hide Input Box';
		var all_divs = document.getElementsByTagName('div');
		for(var i = 0; i < all_divs.length; i++) {
			if(all_divs[i].id.indexOf("input_div_contents") !== -1)
				all_divs[i].style.display = "block"
		}

	}

	function hide_input_box() {
		input_box_state = "hidden";
		var input_box_button = document.getElementById("inputbox_button");
		input_box_button.value="Show Input Box";
		var all_divs = document.getElementsByTagName('div');
		for(var i = 0; i < all_divs.length; i++) {
			if(all_divs[i].id.indexOf("input_div_contents") !== -1)
				all_divs[i].style.display = "none"
		}
	}

	function add_grp_div() {

		if((current_panel !== null) && (current_panel !== GrpPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}
		var button_div = document.getElementById("button_div_id");
		button_div.style.display = "block";

		//add wiki link
		var wiki_panel_div = document.getElementById("wiki_panel_id");
		wiki_panel_div.innerHTML = "<a href='http://en.wikipedia.org/wiki/Group_(mathematics)' target='_blank'>Group Theory - Wikipedia</br><img src='Rubiks_cube.jpg' alt='Rubik cube(picture from wikipedia)' height='160' width='170'><\a>";
		
		GrpPanel.show();
		current_panel = GrpPanel;
		show_input_box();
	}

	function add_vecmat_div() {
		if((current_panel !== null) && (current_panel !== VecMatPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}
		var button_div = document.getElementById("button_div_id");
		button_div.style.display = "block";

		//add wiki link
		var wiki_panel_div = document.getElementById("wiki_panel_id");
		wiki_panel_div.innerHTML = "<a href='http://en.wikipedia.org/wiki/Matrix_(mathematics)' target='_blank'>Vectors and Matrices - Wikipedia</br><img src='linear_spaces.jpg' alt='Linear Spaces(picture from wikipedia)' height='160' width='170'><\a>";
		
		VecMatPanel.show();
		current_panel = VecMatPanel;
		show_input_box();
	}

	function add_poly_div() {
	}

	function add_feature_div() {
	}

	function add_lineq_div() {
		if((current_panel !== null) && (current_panel !== LinEqPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}
		var button_div = document.getElementById("button_div_id");
		button_div.style.display = "block";

		//add wiki link
		var wiki_panel_div = document.getElementById("wiki_panel_id");
		wiki_panel_div.innerHTML = "<a href='http://en.wikipedia.org/wiki/System_of_linear_equations' target='_blank'>Systems of Linear Equations - Wikipedia</br><img src='lineareq.jpg' alt='Linear Equations(picture from wikipedia)' height='160' width='170'><\a>";

		LinEqPanel.show();
		current_panel = LinEqPanel;
		show_input_box();
	}

	function add_calculus_div() {
	}

	function reset_mainview_canvas() {
		var added_input_div = document.getElementById("added_input_id");
		added_input_div.innerHTML="";
		added_input_div.style.display="none";
		var main_view = document.getElementById("main_view_id");
		main_view.innerHTML="";
		main_view.style.display = "none";
		var canvasDiv = document.getElementById("canvas_id");
		if(canvasDiv.style.display === "block") {
			canvasDiv.innerHTML = "<canvas id='main_canvas' class='scanvas' width='512' height='512'>Your browser doesn't support canvas tag. Please update to a recent version in order to take full advantage when viewing this page.</canvas>";
			WebGlContext.initWebGL();
			canvasDiv.style.display = "none";
		}
	}

	//public methods
	return {
		toggle_input_box : toggle_input_box,
		hide_input_box : hide_input_box,
		add_grp_div : add_grp_div,
		add_vecmat_div : add_vecmat_div,
		add_lineq_div : add_lineq_div,
		add_calculus_div : add_calculus_div,
		add_feature_div : add_feature_div
	};
}();

var VecMatPanel = function () {
	var mat_expr_computed = true;
	var command_input_str = "";

	function show() {
        var vecmat_command_panelDiv = document.getElementById("vecmat_commands_panel");
        var vecmatDiv = document.getElementById("vecmat_div_id");
		vecmat_command_panelDiv.style.display = "block";
		vecmatDiv.style.display = "block";
	}

	function hide() {
		var vecmat_command_panelDiv = document.getElementById("vecmat_commands_panel");
        var vecmatDiv = document.getElementById("vecmat_div_id");
		vecmat_command_panelDiv.style.display = "none";
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
					   	"' size='8' maxlength='8'>";
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
					   	"' size='8' maxlength='8'>";
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
			MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
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
			MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
			mat_expr_computed = false;
		}
	}

	function submit_command(command) {
		var request = "command=" + command;
		var _command_input_str = command_input_str.substr(1,command_input_str.length-1);
		if(0 === _command_input_str.length) {
			alert("Please provide the input first(matrix, vector, linear combination).")
		}
		request += "param=" + _command_input_str;
		if(command === 'GET_MAT_EXPR') {
			return submitCommand(request);
		}
		else if(command === 'GET_NORM') {
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("Invalid input. Please provide a valid vector to compute the euclidean norm.");
			}
			else {
				main_view.innerHTML = "<b>euclidean norm: " + result + "</b>";
				main_view.style.display = "block";
			}
		}
		else if(command === 'GET_MAT_DETERMINANT')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("Invalid input. Please provide a valid square matrix for the determinant command.");
			}
			else {
				main_view.innerHTML = "<b>determinant: " + result + "</b>";
				main_view.style.display = "block";
			}
		}
		else if(command === 'GET_MAT_INVERSE')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("Invalid input. Please provide a valid square non-singular matrix for the inverse command.");
			}
			else {
				main_view.innerHTML = "</br><b>inverse matrix: " + result + "</b>";
				main_view.style.display = "block";
			}
		}
		else if(command === 'GET_MAT_LU')
		{
			var main_view = document.getElementById("main_view_id");
			var result = submitCommand(request);
			if(-1 === result.indexOf("$")) {
				alert("Invalid input. Please provide a valid matrix for the LU factorization.");
			}
			else {
				main_view.innerHTML = "</br><b>LU matrix: " + result + "</b>";
				main_view.style.display = "block";
			}
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

//command pannel for linear equations
var LinEqPanel = function () {
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
		if(number <= 0) {
			elem.value = 1;
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
					   	"' size='2' maxlength='2'> $x_" + i.toString() + "$";
				}
				var newcol = newrow.insertCell(-1);
				newcol.innerHTML = "<input type='text' id='result" + (rowsnum + j + 1).toString() +
				   	"' size='2' maxlength='2'> $b_" + (rowsnum + j + 1).toString() + "$";
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
		if(number <= 0) {
			elem.value = 1;
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
					   	"' size='2' maxlength='2'> $x_" + (colsnum + j).toString() + "$";
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
		var lineqTable = document.getElementById("lineq_table_id");
		var rows = lineqTable.getElementsByTagName("tr");
		for(var i = 0; i < rows.length; i++) {
			var cols = rows[i].getElementsByTagName("td");
			for(var j = 0; j < cols.length - 1; j++) {
				if(j != 0)
					system_str+= " + ";
				var val_str = document.getElementById("unknown" + (i+1).toString() + (j+1).toString()).value;
				if(isNaN(val_str) || (val_str == "")) {
					window.alert("Invalid input. Please enter valid coefficients and constant terms!")
					return;
				}
				system_str += val_str + "x_" + (j+1).toString();
			}

			system_str+= " = ";
			var res_str = document.getElementById("result" + (i+1).toString()).value;
			if(isNaN(res_str) || (res_str == "")) {
				window.alert("Invalid input. Please enter valid coefficients and constant terms!")
				return;
			}
			system_str += document.getElementById("result" + (i+1).toString()).value;
			system_str+= "\\\\";
		}
		system_str+="\\end{cases}$";
		var added_input_div = document.getElementById("added_input_id");
		added_input_div.innerHTML = "</br><b>The linear system you provided as input is:</b> </br></br>" + system_str + "</br></br>";
		added_input_div.style.display = "block";
		MainMenu.hide_input_box();
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}
	
	return {
		show : show,
		hide : hide,
		lineq_num_changed : lineq_num_changed,
		unknowns_num_changed : unknowns_num_changed,
		submitSystem : submitSystem
	};
}();

//command panel for group theory
var GrpPanel = function () {
    var state_main_comm = "visible";
	var state_groups = "hidden";
	var state_create_grp = "hidden";
	var group_commands_active = false;	
    
	function show() {
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
        var group_panelDiv = document.getElementById("grp_div_id");
		groupcommand_panelDiv.style.display = "block";
		group_panelDiv.style.display = "block";
	}

	function hide() {
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
        var group_panelDiv = document.getElementById("grp_div_id");
		groupcommand_panelDiv.style.display = "none";
		group_panelDiv.style.display = "none";
	}

	function changeGrpType(type) {
		var generators_div = document.getElementById("generators_div_id");
		if(type.value === "Symmetric Group") {
			generators_div.innerHTML=
				"Enter generator: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='generator_id'>"+
				"&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Add' onclick='GrpPanel.add_generator()'>"+
				"&nbsp;&nbsp;&nbsp;"+
				"<------OR------>&nbsp;"+
				"Add generators for predefined groups: &nbsp;&nbsp;&nbsp;"+
				"<select id='Groups' size='1' onchange='GrpPanel.add_generators(this)'>"+
				"<option value=''></option>"+
				"<option value='S3'>S3</option>"+
				"<option value='S4'>S4</option>"+
				"<option value='D8'>D8</option>"+
				"</select></br></br>";
		}
		else if(type.value === "Cyclic Group") {
			generators_div.innerHTML =
				"Enter group order: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='group_size_id' size='2' maxlength='2'>&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Set generator' onclick='GrpPanel.add_generator()'></br></br>";
		}
		else {//Dihedral Group 
		generators_div.innerHTML =
				"Enter number of sides for the regular polygon: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='group_size_id' size='2' maxlength='2'>&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Set generator' onclick='GrpPanel.add_generator()'></br></br>";
		}
	}

	function add_generator() {
		var generatorTag = document.getElementById("generator_id");
		var grp_typeTag = document.getElementById("grp_sel_id");
		var sizeTag = document.getElementById("group_size_id");
		var newgenTag1 = document.createElement("option");
		var newgenTag2 = document.createElement("option");
		var generatorsTag = document.getElementById("generators_id");
		var size = 0;
		var i = 0;
		
		if(grp_typeTag.value === "Symmetric Group") {
			newgenTag1.innerHTML = generatorTag.value;
			generatorsTag.appendChild(newgenTag1);
		}
		else if(grp_typeTag.value === "Cyclic Group") {
			size = parseInt(sizeTag.value);
			if(size > 20) {
				alert("Maximum allowed group order is 20. Please enter a smaller order.");
				return;
			}
			var perm = new Array();
			for(i = 0; i < size-1; i++) {
				perm[i] = i+2;
			}
			perm[size-1] = 1;
			newgenTag1.innerHTML = "("+perm.toString()+")";
			clear_generators();
			generatorsTag.appendChild(newgenTag1);
		}
		else if(grp_typeTag.value === "Dihedral Group") {
			size = parseInt(sizeTag.value);
			if(size > 20) {
				alert("Maximum allowed size is 20. Please enter a smaller size.");
				return;
			}
			var perm1 = new Array();
			for(i = 0; i < size-1; i++) {
				perm1[i] = i+2;
			}
			perm1[size-1] = 1;

			var perm2 = new Array();
			perm2[0] = 1;
			for(i = 1; i < size; i++) {
				perm2[i] = size - i + 1;
			}

			newgenTag1.innerHTML = "("+perm1.toString()+")";
			newgenTag2.innerHTML = "("+perm2.toString()+")";
			clear_generators();
			generatorsTag.appendChild(newgenTag1);
			generatorsTag.appendChild(newgenTag2);
		}
	}
   
	function add_generators(group) { 
		var generatorsTag = document.getElementById("generators_id");
		var newgenTag1 = document.createElement("option");
		var newgenTag2 = document.createElement("option");
		var newgenTag3 = document.createElement("option");
		generatorsTag .options.length = 0;
		if(group.value === "S3") {
			newgenTag1.innerHTML = "(2,1,3)";
			generatorsTag.appendChild(newgenTag1);
			newgenTag2.innerHTML = "(1,3,2)";
			generatorsTag.appendChild(newgenTag2);
		}
		if(group.value === "S4") {
			newgenTag1.innerHTML = "(2,1,3,4)";
			generatorsTag.appendChild(newgenTag1);
			newgenTag2.innerHTML = "(1,3,2,4)";
			generatorsTag.appendChild(newgenTag2);
			newgenTag3.innerHTML = "(1,2,4,3)";
			generatorsTag.appendChild(newgenTag3);
		}
		else if(group.value === "D8") {
			newgenTag1.innerHTML = "(2,3,4,1)";
			generatorsTag.appendChild(newgenTag1);
			newgenTag2.innerHTML = "(1,4,3,2)";
			generatorsTag.appendChild(newgenTag2);
		}
	}

	function clear_generators() {
		var generatorsTag = document.getElementById("generators_id");
		generatorsTag .options.length = 0;
	}

	function static_vars() {}

	function submit_grp() {
		var generators = new String();
		var generatorsTag = document.getElementById("generators_id");
		var geni = 0;
		for(geni = 0; geni < generatorsTag.length; geni++) {
			 generators += generatorsTag.options[geni].text;
		}
		static_vars.generators = generators;
		var group_selTag = document.getElementById("grp_sel_id");
		static_vars.group_type = group_selTag.options[group_selTag.selectedIndex].value;

		//add to the main div
		var added_input_div = document.getElementById("added_input_id");
		added_input_div.innerHTML = "";
		added_input_div.style.display = "block";
		added_input_div.innerHTML = "</br> <b>The group provided as input is:</b> </br> </br>" + "Group Type: &nbsp;" +
			static_vars.group_type + "</br>" + "Group Generators: &nbsp;" + static_vars.generators + "</br></br>";
		group_commands_active = true;
		MainMenu.hide_input_box();
		return false;
	}

	function submit_command(command) {
		if(group_commands_active === true) {
			var group_types_map = new Object();
			group_types_map["Symmetric Group"] = "SYMMETRIC_GROUP";
			group_types_map["Cyclic Group"] = "CYCLIC_GROUP";
			group_types_map["Dihedral Group"] = "DIHEDRAL_GROUP";

			var request = new String();
			request += "command=" + command;
			request += "param=" + group_types_map[static_vars.group_type];
			request	+= static_vars.generators;
			var main_view = document.getElementById("main_view_id");
			main_view.innerHTML = submitCommand(request);
			main_view.style.display = "block";
			var canvasDiv = document.getElementById("canvas_id");
			if(canvasDiv.style.display === "block") {
				canvasDiv.innerHTML = "<canvas id='main_canvas' class='scanvas' width='512' height='512'>Your browser doesn't support canvas tag. Please update to a recent version in order to take full advantage when viewing this page.</canvas>";
				WebGlContext.initWebGL();
				canvasDiv.style.display = "none";
			}
			if(command === "GET_ELEMENTS") {
				if(static_vars.group_type === "Dihedral Group")	{
					var generatorsTag = document.getElementById("generators_id");
					var size = (generatorsTag.options[0].text.length - 1) / 2;
					if(size < 3 || size > 9)
					{
						return;
					}
					canvasDiv.style.display = "block";
					var main_canvas = document.getElementById("main_canvas");

					var rotateTag = document.createElement("input");
					rotateTag.setAttribute("type","button");
					rotateTag.setAttribute("value","Rotate");
					rotateTag.setAttribute("onclick","GrpPanel.rotate_polygon()"); 
					rotateTag.setAttribute("id","ct1"); 

					var reflectTag = document.createElement("input");
					reflectTag.setAttribute("type","button");
					reflectTag.setAttribute("value","Reflect");
					reflectTag.setAttribute("onclick","GrpPanel.reflect_polygon()"); 
					reflectTag.setAttribute("id","ct2"); 

					var permuTag = document.createElement("ul");
					permuTag.setAttribute("id","list_elem_perm"); 
					permuTag.setAttribute("align","center"); 
					//create permutation
					var permutation = "";
					for(i = 1; i <= size; i++) {
						permutation += i.toString() + " ";
					}
					permutation += "<br>" + permutation;

					permuTag.innerHTML = "<li>" + permutation + "</li>";
					permuTag.style.width = (size * 20).toString() + "px";

					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(rotateTag, main_canvas);
					canvasDiv.insertBefore(reflectTag, main_canvas);
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(permuTag, main_canvas);
					DihedralRep.startScene((generatorsTag.options[0].text.length - 1) / 2);
				}
			}
			window.onbeforeunload = function() { return "Your previous results will be lost !"; };
		}
		else
		{
			window.alert("Please setup a group first!");
		}
	}

	function rotate_polygon() {
		if(DihedralRep.isPendingMove())
		{
			return;
		}
		var permuTag = document.getElementById("list_elem_perm");
		var permutation = permuTag.innerHTML.slice(4, permuTag.innerHTML.length - 5);
		var pos = permutation.indexOf("<br>") + 5;
		permutation = permutation.substr(0, pos - 1) + permutation.charAt(permutation.length-2) +  " " + 
			permutation.substr(pos-1,permutation.length - 2 - pos) + " ";
		permuTag.innerHTML = "<li>" + permutation + "</li>";

		DihedralRep.RotatePolygon();
	}

	function reflect_polygon() {
		if(DihedralRep.isPendingMove())
			return;
		var permuTag = document.getElementById("list_elem_perm");
		var permutation = permuTag.innerHTML.slice(4, permuTag.innerHTML.length - 5);
		var pos = permutation.indexOf("<br>") + 5;
		var size = Math.floor((permutation.length - pos + 1) / 2);

		var index_begin = pos + 1;
		var index_end = permutation.length - 2;
		var left_side = "";
		var right_side = "";
		while(index_begin < index_end) {
			left_side = permutation.charAt(index_begin) + " " + left_side;
			right_side += permutation.charAt(index_end) + " ";
			index_begin += 2;
			index_end -= 2;
		}

		if(size % 2 === 1) {
			permutation = permutation.substr(0, pos);
			permutation += " " + right_side + left_side;
		}
		else {
			var middle = permutation.charAt(index_begin);
			permutation = permutation.substr(0, pos);
			permutation += " " + right_side + middle + " " + left_side;
		}

		permuTag.innerHTML = "<li>" + permutation + "</li>";

		DihedralRep.ReflectPolygon();
	}

	//public methods
	return {
		submit_command : submit_command,
		submit_grp : submit_grp,
		add_generator : add_generator,
		add_generators : add_generators,
		clear_generators : clear_generators,
		changeGrpType : changeGrpType,
		show : show,
		hide : hide,
		reflect_polygon : reflect_polygon,
		rotate_polygon : rotate_polygon
	};

}();


var Tooltip = function () {
	var endalpha = 90, alpha = 0, timer = 20, speed = 10;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.vecmat = "Insert a vector or a matrix or an expression involving operations with both vectors and matrices.";
	tooltip_map.LU_factorization = "Decompose the matrix as a product of a lower triangular matrix and an upper triangular matrix(LU factorization).";
	tooltip_map.mat_determinant = "Compute the determinant (if it is a square matrix($n \\times n$)).";
	tooltip_map.norm = "Compute the euclidean norm for the inserted vector.";
 	tooltip_map.mat_inverse = "Compute the inverse of the matrix($A^{-1}$) if it is not singular.";
	tooltip_map.lineq = "Enter the system of linear equations by first entering the number of equations ($m$) and unknowns ($n$) and then specifying the coefficients $x_1, x_2, ..., x_n$ and the constant terms $b_1, b_2, ..., b_m$.";
	tooltip_map.solve_lineq = "Solve the linear system.";
	tooltip_map.select = "Select a predefined group.";
	tooltip_map.s3 = "Symmetric group of order 3.";
	tooltip_map.d8 = "Dihedral group of order 8.";
	tooltip_map.generator = "Generators are of the form $(x_1,x_2,x_3,...)$ which represents the permutation 1->$x_1$, 2->$x_2$, 3->$x_3$, ...";
	tooltip_map.source = "Visit the project repository on Google Code.";
	tooltip_map.get_elem = "Compute the elements of the group.";
	tooltip_map.get_center = "Compute the Center subgroup(elements that commute with all the elements of the group).";
	tooltip_map.get_cgraph = "Compute the Cayley graph of the group(colored directed graph).";
	tooltip_map.get_rel = "Compute the defining relations of the group.";

return{	
	show: function (callee)
	{
		if(tooltip == null)
		{
			tooltip = document.createElement("div");
			tooltip.setAttribute("id","tooltip_id");
			var command_panelDiv = document.getElementById("command_panel");
			command_panelDiv.appendChild(tooltip);
			tooltip.style.opacity = 0;
			tooltip.style.filter = 'alpha(opacity=0)';
		}

		tooltip.style.display = "block";
		tooltip.innerHTML = tooltip_map[callee];
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){Tooltip.fade(1)},timer);
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	},

	fade: function (d)
	{
		var a = alpha;
		if((a !== endalpha && d === 1) || (a !== 0 && d === -1))
		{
			var i = speed;
			if(endalpha - a < speed && d === 1){
			i = endalpha - a;
		}
		else if(alpha < speed && d === -1)
		{
			i = a;
		}
		alpha = a + (i * d);
		tooltip.style.opacity = alpha * .01;
		tooltip.style.filter = "alpha(opacity=" + alpha + ")";
		}
		else
		{
			clearInterval(tooltip.timer);
			if(d === -1)
			{
				tooltip.style.display = "none";
			}
		}
	},

	hide: function ()
	{
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){Tooltip.fade(-1)},timer);
	}
};
}(); 
    
