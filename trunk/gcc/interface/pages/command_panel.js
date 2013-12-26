
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

//main panel logic
var MainMenu = function () {
	var current_panel = PlottingPanel;

	function showIntCompdiv() {
		var intcompDiv = document.getElementById("interactive_comp");
		var scriptingDiv = document.getElementById("scripting");
		scriptingDiv.style.display = "none";
		intcompDiv.style.display = "block";
	}

	function showScriptingDiv() {
		var scriptingDiv = document.getElementById("scripting");
		var intcompDiv = document.getElementById("interactive_comp");
		intcompDiv.style.display = "none";
		scriptingDiv.style.display = "block";
	}

	function reset_tabs() {
		var plot_li = document.getElementById("li_plot_id");
		var plot_a = document.getElementById("a_plot_id");
		plot_li.className = "";
		plot_a.className = "";

		var poly_li = document.getElementById("li_poly_id");
		var poly_a = document.getElementById("a_poly_id");
		poly_li.className = "";
		poly_a.className = "";

		var lineq_li = document.getElementById("li_lineq_id");
		var lineq_a = document.getElementById("a_lineq_id");
		lineq_li.className = "";
		lineq_a.className = "";

		var dif_li = document.getElementById("li_diff_id");
		var dif_a = document.getElementById("a_diff_id");
		dif_li.className = "";
		dif_a.className = "";

		var grp_li = document.getElementById("li_grp_id");
		var grp_a = document.getElementById("a_grp_id");
		grp_li.className = "";
		grp_a.className = "";

		var mat_li = document.getElementById("li_mat_id");
		var mat_a = document.getElementById("a_mat_id");
		mat_li.className = "";
		mat_a.className = "";
	}

	function showDiv(panel) {
		var calculusDiv = document.getElementById("calculus_panel");
		var linalgDiv = document.getElementById("linear_algebra_panel");
		var probDiv = document.getElementById("probabilities_panel");
		var absalgDiv = document.getElementById("absalg_panel");
		calculusDiv.style.display="none";
		linalgDiv.style.display="none";
		probDiv.style.display="none";
		absalgDiv.style.display="none";
		if(panel === "calculus") {
			calculusDiv.style.display="block";
			add_plotting_div();
		}
		else if(panel === "linalg")	{
			linalgDiv.style.display="block";
			add_lineq_div();
		}
		else if(panel === "prob") {
			probDiv.style.display="block";
		}
		else if(panel === "absalg")	{
			absalgDiv.style.display="block";
			add_grp_div();
		}
	}

	function add_grp_div() {

		if((current_panel !== null) && (current_panel !== GrpPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var grp_li = document.getElementById("li_grp_id");
		var grp_a = document.getElementById("a_grp_id");
		grp_li.className = "selected";
		grp_a.className = "selected";

		GrpPanel.show();
		current_panel = GrpPanel;
	}

	function add_vecmat_div() {
		if((current_panel !== null) && (current_panel !== VecMatPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var mat_li = document.getElementById("li_mat_id");
		var mat_a = document.getElementById("a_mat_id");
		mat_li.className = "selected";
		mat_a.className = "selected";

		VecMatPanel.show();
		current_panel = VecMatPanel;
	}

	function add_poly_div() {
	if((current_panel !== null) && (current_panel !== PolyPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var poly_li = document.getElementById("li_poly_id");
		var poly_a = document.getElementById("a_poly_id");
		poly_li.className = "selected";
		poly_a.className = "selected";

		PolyPanel.show();
		current_panel = PolyPanel;
	}

	function add_plotting_div() {
		if((current_panel !== null) && (current_panel !== PlottingPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var plot_li = document.getElementById("li_plot_id");
		var plot_a = document.getElementById("a_plot_id");
		plot_li.className = "selected";
		plot_a.className = "selected";

		PlottingPanel.show();
		current_panel = PlottingPanel;
	}

	function add_lineq_div() {
		if((current_panel !== null) && (current_panel !== LinEqPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var lineq_li = document.getElementById("li_lineq_id");
		var lineq_a = document.getElementById("a_lineq_id");
		lineq_li.className = "selected";
		lineq_a.className = "selected";

		LinEqPanel.show();
		current_panel = LinEqPanel;
	}

	function add_diff_div() {
		if((current_panel !== null) && (current_panel !== DiffPanel)) {
			current_panel.hide();
			reset_mainview_canvas();
		}

		reset_tabs();
		var diff_li = document.getElementById("li_diff_id");
		var diff_a = document.getElementById("a_diff_id");
		diff_li.className = "selected";
		diff_a.className = "selected";

		DiffPanel.show();
		current_panel = DiffPanel;
	}

	function reset_mainview_canvas() {
		var added_input_div1 = document.getElementById("added_input_id1");
		var added_input_div2 = document.getElementById("added_input_id2");
		var added_input_div3 = document.getElementById("added_input_id3");
		var added_input_div4 = document.getElementById("added_input_id4");
		var added_input_div5 = document.getElementById("added_input_id5");
		added_input_div1.innerHTML="";
		added_input_div1.style.display="none";
		added_input_div2.innerHTML="";
		added_input_div2.style.display="none";
		added_input_div3.innerHTML="";
		added_input_div3.style.display="none";
		added_input_div4.innerHTML="";
		added_input_div4.style.display="none";
		added_input_div5.innerHTML="";
		added_input_div5.style.display="none";

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
		add_grp_div : add_grp_div,
		add_vecmat_div : add_vecmat_div,
		add_lineq_div : add_lineq_div,
		add_diff_div : add_diff_div,
		add_poly_div : add_poly_div,
		add_plotting_div : add_plotting_div,
		showIntCompdiv : showIntCompdiv,
		showScriptingDiv : showScriptingDiv,
		showDiv : showDiv
	};
}();

