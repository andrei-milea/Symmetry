//global helper function
function insertAfter(referenceNode, newNode) {
	referenceNode.parentNode.insertBefore(newNode, referenceNode.nextSibling);
}

//toolbox
var ToolBox = function () {
	var slideNo = 1;
	var currentSlide = 1;
	var addedDivzIndex = 1;
	var insertTop = 0;
	var insertLeft = 0;
	var offY = 0;
	var offX = 0;
	var dragg_width = 0;
	var dragg_height = 0;

	function addSlide() {
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNo++;
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
		new_div = document.createElement("div");
		new_div.setAttribute("id", "slide_id_" + slideNo.toString());
		new_div.className = "slide_div";
		new_div.onclick = ToolBox.showContextMenu;
		new_div.style.display = "none";
		insertAfter(document.getElementById("slide_id_1"), new_div);
	}

	function deleteLastSlide() {
		if(slideNo === 1)
			return;

		if(currentSlide === slideNo) {
			currentSlide--;
			var slide = document.getElementById("slide_id_" + currentSlide.toString());
			slide.style.display = "block";
		}

		var last_slide = document.getElementById("slide_id_" + slideNo.toString());
		last_slide.parentNode.removeChild(last_slide);
		slideNo--;

		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
	}

	function prevSlide() {
		if(currentSlide === 1)
			return;

		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "none";
		currentSlide--;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "block";
	}

	function nextSlide() {
		if(currentSlide === slideNo)
			return;

		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "none";
		currentSlide++;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "block";
	}

	function onCursorChange(sel) {
		var slides = document.getElementsByClassName("slide_div");
		if("Move & Resize" == sel.options[sel.selectedIndex].value) {
			for(i = 0; i < slides.length; i++)
				slides[i].style.cursor = "pointer";
			addListeners();
		}
		else if("Insert" == sel.options[sel.selectedIndex].value){
			for(i = 0; i < slides.length; i++)
				slides[i].style.cursor = "cell";
			removeListeners();
		}
		else {
			for(i = 0; i < slides.length; i++)
				slides[i].style.cursor = "default";
			removeListeners();
		}
	}

	function divMove(e){
		var div = e.target;
		if(div.className !== "draggable") {
			div = e.target.parentNode;
			if(div.className !== "draggable")
				return;
		}
		
		div.style.position = 'absolute';
		div.style.top = (e.clientY - offY) + 'px';
		div.style.left = (e.clientX - offX) + 'px';
	}

	function mouseDown(e){
		var div = e.target;
		if(div.className !== "draggable") {
			div = e.target.parentNode;
			if(div.className !== "draggable")
				return;
		}
		offY = e.clientY - parseInt(div.offsetTop);
		offX = e.clientX - parseInt(div.offsetLeft);
		window.addEventListener('mousemove', ToolBox.divMove, true);

		dragg_width = div.clientWidth;
		dragg_height = div.clientHeight;
	}

	function mouseUp(e) {
		window.removeEventListener('mousemove', ToolBox.divMove, true);

		var div = e.target;
		if(div.className !== "draggable") {
			div = e.target.parentNode;
			if(div.className !== "draggable") {
				div = e.target.parentNode.parentNode;
				if(div.className !== "draggable")
					return;
			}
		}
		if(dragg_width !== div.clientWidth || dragg_height !== div.clientHeight) {
			if(div.childNodes[0].id.indexOf("canvas_id_") === 0) {
				div.childNodes[0].childNodes[0].width = Math.min(div.childNodes[0].clientWidth, div.childNodes[0].clientHeight) - 20;
				div.childNodes[0].childNodes[0].height = div.childNodes[0].childNodes[0].width;

				div.childNodes[0].childNodes[0].clientWidth = div.childNodes[0].childNodes[0].width;
				div.childNodes[0].childNodes[0].clientHeight = div.childNodes[0].childNodes[0].width;
			}
		}	
		
	}

	function addListeners(){
		var divs = document.getElementsByClassName("draggable");
		for(i = 0; i < divs.length; i++) {
			divs[i].addEventListener('mousedown', ToolBox.mouseDown, false);
			divs[i].style.resize = "both";
		}
		window.addEventListener('mouseup', ToolBox.mouseUp, false);
	}

	function removeListeners(){
		var divs = document.getElementsByClassName("draggable");
		for(i = 0; i < divs.length; i++) {
			divs[i].removeEventListener('mousedown', ToolBox.mouseDown, false);
			divs[i].style.resize = "none";
		}
		window.removeEventListener('mouseup', ToolBox.mouseUp, false);
	}

	function preview() {
	}

	function save() {
	}

	/////////////////context menu functionality//////////////////////
	function showContextMenu(event) {
		var slideDiv = event.target;
		if("cell" !== slideDiv.style.cursor)
			return;
		var menu = document.getElementById("context_menu_id");
		insertTop = event.clientY;
		insertLeft = event.clientX - 50;
		menu.style.top = event.clientY.toString() + "px";
		menu.style.left = (event.clientX - 50).toString() + "px";
		menu.style.display = "block";
	}

	function hideContextMenu() {
		var menu = document.getElementById("context_menu_id");
		menu.style.display = "none";
	}

	function onElementChange(sel) {
		var plot_div = document.getElementById("plotting_div_id");
		var poly_div = document.getElementById("insert_poly_id");
		var matrix_div = document.getElementById("insert_matrix_id");
		var lineq_div = document.getElementById("insert_lineq_id");
		var chart_div = document.getElementById("insert_chart_id");
		plot_div.style.display = "none";
		poly_div.style.display = "none";
		matrix_div.style.display = "none";
		lineq_div.style.display = "none";
		chart_div.style.display = "none";

		if(0 === sel.selectedIndex)
			plot_div.style.display = "block";
		else if(1 === sel.selectedIndex)
			poly_div.style.display = "block";
		else if(2 === sel.selectedIndex)
			matrix_div.style.display = "block";
		else if(4 === sel.selectedIndex)
			lineq_div.style.display = "block";
		else if(5 === sel.selectedIndex)
			chart_div.style.display = "block";

		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	}

	function addTextArea() {
		new_div = document.createElement("div");
		new_div.innerHTML = "<textarea class='boxText'></textarea>";
		addDraggableDiv(new_div);
		hideContextMenu();
	}

	function addDraggableDiv(new_div) {

		var slide = document.getElementById("slide_id_" + currentSlide.toString());
		new_div.className = "draggable";
		new_div.style.position = "absolute";
		new_div.style.top = insertTop.toString() + "px";
		new_div.style.left = insertLeft.toString() + "px";

		new_div.style.zIndex = addedDivzIndex;

		addedDivzIndex++;

		slide.appendChild(new_div);

		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);

	}

	function addParagraph() {
		var parag_sel = document.getElementById("paragraph_select_id");
		var parag_txt = document.getElementById("paragraph_text_id").value;
		var parag_title = parag_sel.options[parag_sel.selectedIndex].value;

		new_div = document.createElement("div");
		h1 = document.createElement("h1");
		txt_div = document.createElement("div");
		h1.innerHTML = parag_title;
		txt_div.innerHTML = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + parag_txt + "</br></br>";

		new_div.style.border = "2px solid #6b727c";

		new_div.appendChild(h1);
		new_div.appendChild(txt_div);
		addDraggableDiv(new_div);
	}

	function addChart(new_div, type, labels, data) {
		
		new_div.innerHTML =	<canvas id="" width="400" height="400"></canvas>;
	}

	function addMathElem() {
		var sel = document.getElementById("paragraph_select_id");
		new_div = document.createElement("div");
		new_div.style.border = "2px solid #6b727c";

		if(0 === sel.selectedIndex) {
			var canvasDiv = document.createElement("div");
			var idNoStr = addedDivzIndex.toString();
			canvasDiv.setAttribute("id", "canvas_id_" + idNoStr);
			canvasDiv.style.width = "100%";
			canvasDiv.style.height = "100%";
			new_div.appendChild(canvasDiv);
			addDraggableDiv(new_div);
			PlottingPanel.submitFct("canvas_id_" + idNoStr, "main_canvas_" + idNoStr);
		}
		else if(1 === sel.selectedIndex) {
			var _tex_input_str = "$p(x) = ";
			var command_input_str = "";
			var polyTable = document.getElementById("poly_table_id");
			var rows = polyTable.getElementsByTagName("tr");
			var cols = rows[0].getElementsByTagName("td");
			for(var j = 0; j < cols.length; j++) {
				if(j != 0) {
					_tex_input_str += " + ";
					command_input_str += ",";
				}
				var val_str = document.getElementById("entry" + (j+1).toString()).value;
				if(isNaN(val_str) || (val_str == "")) {
					window.alert("Invalid input. Please enter valid coefficients and constant terms!")
					return;
				}
				if(j === 0)
					_tex_input_str += val_str;
				else if(j == 1)
					_tex_input_str += val_str + " x";
				else
					_tex_input_str += val_str + " x^" + (j).toString();
		
				command_input_str += val_str;
			}
			_tex_input_str += "$";
			new_div.innerHTML =	_tex_input_str;
			addDraggableDiv(new_div);
		}
		else if(2 === sel.selectedIndex) {
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
			command_input_str += "\\end{bmatrix}$";
			new_div.innerHTML =	command_input_str;
			addDraggableDiv(new_div);
		}
		else if(4 === sel.selectedIndex) {
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
			system_str += "\\end{cases}$";
			command_input_str += "\\end{bmatrix}$";

			new_div.innerHTML =	system_str;
			addDraggableDiv(new_div);
		}
		else if(4 === sel.selectedIndex) {
			var chart = document.getElementById("chart_select_id");
			var labels = document.getElementById("labels_id");
			var data = document.getElementById("data_id");

			addChart(new_div, chart.selectedIndex, labels.value, data.value);
			addDraggableDiv(new_div);
		}
	}
	///////////////////////////////////////////////////////////////

	//public methods
	return {
		addSlide : addSlide,
		deleteLastSlide : deleteLastSlide,
		preview : preview,
		save : save,
		prevSlide : prevSlide,
		nextSlide : nextSlide,
		onCursorChange : onCursorChange,
		divMove : divMove,
		mouseDown : mouseDown,
		mouseUp : mouseUp,
		showContextMenu : showContextMenu,
		hideContextMenu : hideContextMenu,
		onElementChange : onElementChange,
		addTextArea : addTextArea,
		addParagraph : addParagraph,
		addMathElem : addMathElem
	};
}();

