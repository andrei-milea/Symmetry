//context menu
var ContextMenu = function () {

	function show(event) {
		var slideDiv = event.target;
		if("cell" !== slideDiv.style.cursor)
			return;
		var menu = document.getElementById("context_menu_id");
		menu.style.top = event.clientY.toString() + "px";
		menu.style.left = (event.clientX - 20).toString() + "px";
		menu.style.display = "block";
	}

	function hide() {
		var menu = document.getElementById("context_menu_id");
		menu.style.display = "none";
	}

	function selection(id) {
		if("text" === id) {
			var slide = document.getElementById("slide_id");
			slide.innerHTML += "<textarea rows='10' cols='30'></textarea>";
		}
		hide();
	}

	//public methods
	return {
		show : show,
		selection : selection
	};
}();

