//command panel  logic for vector and matrix computations
var DiffPanel = function () {

	function show() {
        var diffDiv = document.getElementById("diff_div_id");
		diffDiv.style.display = "block";
	}

	function hide() {
        var diffDiv = document.getElementById("diff_div_id");
		diffDiv.style.display = "none";
	}

	function submitFct() {
		var fct_area = document.getElementById("fct_area_id1");
		var command_input_str = fct_area.value.trim();
		var request = "command=GET_FNC_DIFF";
		if(0 === command_input_str.length) {
			alert("Please provide the function first.")
			return;
		}
		request += "param=" + command_input_str;
		var result = submitCommand(request);
		if(-1 != result.indexOf("Error")) {
			alert("error : " + result);
			return;
		}

		var main_view = document.getElementById("main_view_id");
		main_view.innerHTML = "<br/><b>" + result + "</b></br>";
		main_view.style.display = "block";
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	return {
		show : show,
		hide : hide,
		submitFct : submitFct
	};
}();

