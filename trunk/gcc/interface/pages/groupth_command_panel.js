
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
				"</select><br/><br/>";
		}
		else if(type.value === "Cyclic Group") {
			generators_div.innerHTML =
				"Enter group order: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='group_size_id' size='2' maxlength='2'>&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Set generator' onclick='GrpPanel.add_generator()'><br/><br/>";
		}
		else {//Dihedral Group 
		generators_div.innerHTML =
				"Enter number of sides for the regular polygon: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='group_size_id' size='2' maxlength='2'>&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Set generator' onclick='GrpPanel.add_generator()'><br/><br/>";
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
		var added_input_div = document.getElementById("added_input_id1");
		added_input_div.innerHTML = "";
		added_input_div.style.display = "block";
		added_input_div.innerHTML = "<br/> <b>The group provided as input is:</b> <br/> <br/>" + "Group Type: &nbsp;" 			+ static_vars.group_type + "<br/>" + "Group Generators: &nbsp;" + static_vars.generators + "<br/><br/>";
		group_commands_active = true;
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
					permutation += "<br/>" + permutation;

					permuTag.innerHTML = "<li>" + permutation + "</li>";
					permuTag.style.width = (size * 20).toString() + "px";

					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(rotateTag, main_canvas);
					canvasDiv.insertBefore(reflectTag, main_canvas);
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(permuTag, main_canvas);
					DihedralRep.startAnim((generatorsTag.options[0].text.length - 1) / 2);
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
		var pos = permutation.indexOf("<br/>") + 5;
		permutation = permutation.substr(0, pos - 1) + permutation.charAt(permutation.length-2) +  " " + 
			permutation.substr(pos-1,permutation.length - 2 - pos) + " ";
		permuTag.innerHTML = "<li>" + permutation + "</li>";

		DihedralRep.rotatePolygon();
	}

	function reflect_polygon() {
		if(DihedralRep.isPendingMove())
			return;
		var permuTag = document.getElementById("list_elem_perm");
		var permutation = permuTag.innerHTML.slice(4, permuTag.innerHTML.length - 5);
		var pos = permutation.indexOf("<br/>") + 5;
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

		DihedralRep.reflectPolygon();
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


