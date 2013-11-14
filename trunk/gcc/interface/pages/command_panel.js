
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
	var current_panel = null;
	var input_box_state = "hidden";


	function show_input_box() {
		input_box_state = "shown";
		var all_divs = document.getElementsByTagName('div');
		for(var i = 0; i < all_divs.length; i++) {
			if(all_divs[i].id.indexOf("input_div_contents") !== -1)
				all_divs[i].style.display = "block"
		}

	}

	function hide_input_box() {
		input_box_state = "hidden";
		var all_divs = document.getElementsByTagName('div');
		for(var i = 0; i < all_divs.length; i++) {
			if(all_divs[i].id.indexOf("input_div_contents") !== -1)
				all_divs[i].style.display = "none"
		}
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

		var dif_li = document.getElementById("li_dif_id");
		var dif_a = document.getElementById("a_dif_id");
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
		show_input_box();
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
		show_input_box();
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
		show_input_box();
	}

	function add_feature_div() {
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
		show_input_box();
	}

	function add_calculus_div() {
	}

	function reset_mainview_canvas() {
		var added_input_div1 = document.getElementById("added_input_id1");
		var added_input_div2 = document.getElementById("added_input_id2");
		var added_input_div3 = document.getElementById("added_input_id3");
		var added_input_div4 = document.getElementById("added_input_id4");
		added_input_div1.innerHTML="";
		added_input_div1.style.display="none";
		added_input_div2.innerHTML="";
		added_input_div2.style.display="none";
		added_input_div3.innerHTML="";
		added_input_div3.style.display="none";
		added_input_div4.innerHTML="";
		added_input_div4.style.display="none";

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
		hide_input_box : hide_input_box,
		add_grp_div : add_grp_div,
		add_vecmat_div : add_vecmat_div,
		add_lineq_div : add_lineq_div,
		add_calculus_div : add_calculus_div,
		add_poly_div : add_poly_div,
		add_feature_div : add_feature_div
	};
}();

var Tooltip = function () {
	var endalpha = 70, alpha = 0, timer = 20, speed = 5;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.discriminant = "Compute the discriminant: $\\Delta = a_n^{2n-2}\\prod_{i < j}(r_i - r_j)^2$, where $r_1, ... r_n$ are the roots(counting multiplicity).";
	tooltip_map.poly = "Insert a polynomial with real or integer coefficients by specifying the degree and adding coefficients starting with the leading term (on the leftmost input field).";
	tooltip_map.roots = "Compute solutions to P(x) = 0.";
	tooltip_map.plot = "Plot the graph of the polynomial.";
	tooltip_map.solveg_lineq = "Solve an underdetermined system (obtain the general solution - $x_{particular}$ + nullspace).";
	tooltip_map.gramsch = "Compute an orthonormal basis given a matrix with linearly independent columns (the Q matrix from the $A = Q R$ factorization using Gram-Schmidt).";
	tooltip_map.mat_rref = "Compute the Row Reduced Echelon Form for the given matrix(Gaussian-Jordan elimination).";
	tooltip_map.sym_codes = "Use the SYMMETRY INTERPRETED LANGUAGE directly in the browser to perform and develop advanced computations using the provided API.";
	tooltip_map.approx_lineq = "Find approximate solutions - if the system is overdetermined - by using the least squares approach.";
	tooltip_map.vecmat = "Insert a vector or a matrix or an expression (in latex syntax) involving operations with both vectors and matrices - a linear combination (an example is provided in the input field).";
	tooltip_map.eigenvalues = "Compute the eigenvalues (if it is a square matrix ($n \\times n$)).";
	tooltip_map.mat_determinant = "Compute the determinant and the trace (if it is a square matrix($n \\times n$)).";
	tooltip_map.norm = "Compute the euclidean norm for the input vector.";
 	tooltip_map.mat_inverse = "Compute the inverse of the matrix ($A^{-1}$) if it is not singular.";
	tooltip_map.lineq = "Enter the system of linear equations by first entering the number of equations ($m$) and unknowns ($n$) and then specifying the coefficients $x_1, x_2, ..., x_n$ and the constant terms $b_1, b_2, ..., b_m$.";
	tooltip_map.solve_lineq = "Solve the linear system if it has a single uniques solution.";
	tooltip_map.generator = "Generators should be provided as a permutation array $(x_1,x_2,x_3,...)$ which represents the permutation 1->$x_1$, 2->$x_2$, 3->$x_3$, ...";
	tooltip_map.get_elem = "Compute the elements of the group.";
	tooltip_map.get_center = "Compute the Center subgroup (elements that commute with all the elements of the group).";
	tooltip_map.get_cgraph = "Compute the Cayley graph of the group (colored directed graph).";
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
		
		if(tooltip.offsetTop < window.scrollY)
		{
			tooltip.style.top=window.scrollY + 370;
		}
		if(tooltip.offsetTop + tooltip.offsetHeight > window.scrollY + 650)
		{
			tooltip.style.top=window.scrollY + 370;
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
    
