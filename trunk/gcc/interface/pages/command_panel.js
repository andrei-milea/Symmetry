var MainMenu = function () {
	var current_panel = null;

	function reloadPage() {
		document.location.reload();
	}

	function add_grp_div() {

		if((current_panel !== null) && (current_panel !== GrpPanel)) {
			reloadPage();
		}
		GrpPanel.show();
		current_panel = GrpPanel;
	}

	function add_linalg_div() {
		reloadPage();
	}

	function add_calculus_div() {
		reloadPage();
	}

	//public methods
	return {
		add_grp_div : add_grp_div,
		add_linalg_div : add_linalg_div,
		add_calculus_div : add_calculus_div
	};
}();

//command panel for group theory
var GrpPanel = function () {
    var state_main_comm = "visible";
	var state_groups = "hidden";
	var state_create_grp = "hidden";
	var group_commands_active = false;	
    
	function show_group_commands_panel() {
		add_create_grp_div();
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
		groupcommand_panelDiv.style.display = "block";
	}

	function hide_group_commands_panel() {
		remove_create_grp_div();
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
		groupcommand_panelDiv.style.display = "none";
	}

	function add_create_grp_div() {	
		if(state_create_grp === "hidden") {
			var command_panelDiv = document.getElementById("command_panel");
			var createGrpDivTag = document.createElement("div");
			createGrpDivTag.setAttribute("id", "grp_div_id");
			createGrpDivTag.setAttribute("onmouseover", "Tooltip.show('generator')");
			createGrpDivTag.setAttribute("onmouseout", "Tooltip.hide()");
			createGrpDivTag.innerHTML="&nbsp;&nbsp;&nbsp;"+
				"<form onSubmit='return GrpPanel.submit_grp()'>"+
				"<select id='grptype_sel_id' name='Group Type' onchange=''>"+
				"<option>Small Permutation Groups</option>"+
				"</select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+
				"Select a small permutation group type: &nbsp;&nbsp;&nbsp;"+
				"<select id='grp_sel_id' name='Group' onchange='GrpPanel.changeGrpType(this)'>"+
				"<option>Symmetric Group</option>"+
				"<option>Cyclic Group</option>"+
				"<option>Dihedral Group</option>"+
				"</select>"+
				"</br><hr /></br>"+
				"<div id='generators_div_id'>"+
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
				"</select></br></br>"+
				"</div>"+
				"Generators:</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+
				"<select id='generators_id' size='5' style='Width:200' ></select>"+
				"&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Clear' onclick='GrpPanel.clear_generators()'>"+
				"</br></br>After adding the generators hit &nbsp;&nbsp;&nbsp;"+
				"<input type='submit' value='Go'></form>"+
				"</br>";
			command_panelDiv.appendChild(createGrpDivTag);
			state_create_grp = "visible";
		}
	}

	function remove_create_grp_div() {
		if(state_create_grp === "visible") {
			var command_panelDiv = document.getElementById("command_panel");
			grp_divTag = document.getElementById("grp_div_id");
			command_panelDiv.removeChild(grp_divTag);
			state_create_grp = "hidden";
		}
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
				"<input type='text' id='group_size_id'>&nbsp;&nbsp;&nbsp;"+
				"<input type='button' value='Set generator' onclick='GrpPanel.add_generator()'></br></br>";
		}
		else {//Dihedral Group 
		generators_div.innerHTML =
				"Enter number of sides for the regular polygon: &nbsp;&nbsp;&nbsp;"+
				"<input type='text' id='group_size_id'>&nbsp;&nbsp;&nbsp;"+
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
		var grpDiv = document.getElementById("grp_div_id");
		var group_propertyDiv_ = document.getElementById("group_property_div_id");
		if((group_propertyDiv_ !== undefined) && (group_propertyDiv_ !== null))
			grpDiv.removeChild(group_propertyDiv_);
		var group_propertyDiv = document.createElement("div");
		grpDiv.appendChild(group_propertyDiv);
		group_propertyDiv.setAttribute("id", "group_property_div_id");
		var property_tableTag = document.createElement("table");
		property_tableTag.setAttribute("id", "grp_table_id");
		property_tableTag.setAttribute("border", "1");
		group_propertyDiv.appendChild(property_tableTag);

		add_group_property("Group Type", static_vars.group_type);
		add_group_property("Group Generators", static_vars.generators);
		group_commands_active = true;
		return false;
	}

	function add_group_property(property, value) {
		var property_tableTag = document.getElementById("grp_table_id");
		var rowTag = document.createElement("tr");
		var cell1Tag = document.createElement("td");
		var cell2Tag = document.createElement("td");
		var content1Tag = document.createTextNode(property);
		var content2Tag = document.createTextNode(value);
		cell1Tag.appendChild(content1Tag);
		cell2Tag.appendChild(content2Tag);
		rowTag.appendChild(cell1Tag);
		rowTag.appendChild(cell2Tag);
		property_tableTag.appendChild(rowTag);
	}

	function submit_grp_command(command) {
		if(group_commands_active === true) {
			var group_types_map = new Object();
			group_types_map["Symmetric Group"] = "SYMMETRIC_GROUP";
			group_types_map["Cyclic Group"] = "CYCLIC_GROUP";
			group_types_map["Dihedral Group"] = "DIHEDRAL_GROUP";

			var request = new String();
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

			request = "id=" + sessionkeyTag.value;
			request += "command=" + command;
			request += "param=" + group_types_map[static_vars.group_type];
			request	+= static_vars.generators;
			xmlhttp.open("GET", request, false);
			xmlhttp.send();
			var main_view = document.getElementById("main_view_id");
			main_view.innerHTML=xmlhttp.responseText;
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
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
					canvasDiv.insertBefore(document.createElement("br"), main_canvas);
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
		submit_grp_command : submit_grp_command,
		submit_grp : submit_grp,
		add_generator : add_generator,
		add_generators : add_generators,
		clear_generators : clear_generators,
		changeGrpType : changeGrpType,
		show : show_group_commands_panel,
		hide : hide_group_commands_panel,
		reflect_polygon : reflect_polygon,
		rotate_polygon : rotate_polygon
	};

}();


var Tooltip = function () {
	var endalpha = 70, alpha = 0, timer = 20, speed = 10;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.groupTheory = "Explore and visualize concepts in Group Theory";
 	tooltip_map.linAlg = "Perform computations and analize the geometric meaning of different concepts in Linear Algebra(matrices, systems of linear equations, vector spaces, transformations)";
	tooltip_map.calculus = "Perform Calculus computations and analyze the behaviour of functions (function graphing)";
	tooltip_map.tutorials = "Visit our tutorial videos on our Youtube page.";
	tooltip_map.prev_panel = "Go back to the previous panel (cancel ongoing action).";
	tooltip_map.select = "Select a predefined group.";
	tooltip_map.s3 = "Symmetric group of order 3.";
	tooltip_map.d8 = "Dihedral group of order 8.";
	tooltip_map.generator = "Generators are of the form (x1,x2,x3,...) which represents the permutation 1->x1, 2->x2, 3->x3, ...";
	tooltip_map.source = "Visit the project repository on Google Code.";
	tooltip_map.get_elem = "Compute group elements using Dimono algorithm(permutation groups).";
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
    
