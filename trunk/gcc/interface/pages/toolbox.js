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
		if("Move" == sel.options[sel.selectedIndex].value) {
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
		}
	}

	function divMove(e){
		var div = e.target.parentNode;
		if(div.className !== "draggable")
			return;
		div.style.position = 'absolute';
		div.style.top = (e.clientY-offY) + 'px';
		div.style.left = (e.clientX-offX) + 'px';
	}

	function mouseDown(e){
		var div = e.target.parentNode;
		offY= e.clientY-parseInt(div.offsetTop);
		offX= e.clientX-parseInt(div.offsetLeft);
		window.addEventListener('mousemove', ToolBox.divMove, true);
	}

	function mouseUp() {
		window.removeEventListener('mousemove', ToolBox.divMove, true);
	}

	function addListeners(){
		var divs = document.getElementsByClassName("draggable");
		for(i = 0; i < divs.length; i++) {
			divs[i].addEventListener('mousedown', ToolBox.mouseDown, false);
		}
		window.addEventListener('mouseup', ToolBox.mouseUp, false);
	}

	function removeListeners(){
		var divs = document.getElementsByClassName("draggable");
		for(i = 0; i < divs.length; i++) {
			divs[i].removeEventListener('mousedown', ToolBox.mouseDown, false);
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
		plot_div.style.display = "none";
		poly_div.style.display = "none";
		matrix_div.style.display = "none";
		lineq_div.style.display = "none";

		if(0 === sel.selectedIndex)
			plot_div.style.display = "block";
		else if(1 === sel.selectedIndex)
			poly_div.style.display = "block";
		else if(2 === sel.selectedIndex)
			matrix_div.style.display = "block";
		else if(4 === sel.selectedIndex)
			lineq_div.style.display = "block";
	}

	function addTextArea() {
		var slide = document.getElementById("slide_id_" + currentSlide.toString());
		new_div = document.createElement("div");
		new_div.className = "draggable";
		new_div.innerHTML = "<textarea class='boxText'></textarea>";
		
		new_div.style.position = "absolute";
		new_div.style.top = insertTop.toString() + "px";
		new_div.style.left = insertLeft.toString() + "px";

		addedDivzIndex++;
		new_div.style.zIndex = addedDivzIndex;
		slide.appendChild(new_div);
		hideContextMenu();
	}

	function addParagraph() {
		var slide = document.getElementById("slide_id_" + currentSlide.toString());
		var parag_sel = document.getElementById("paragraph_select_id");
		var parag_txt = document.getElementById("paragraph_text_id").value;
		var parag_title = parag_sel.options[parag_sel.selectedIndex].value;

		new_div = document.createElement("div");
		h1 = document.createElement("h1");
		txt_div = document.createElement("div");
		h1.innerHTML = parag_title;
		txt_div.innerHTML = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + parag_txt + "</br></br>";

		new_div.className = "draggable";
		new_div.style.border = "2px solid #6b727c";

		new_div.appendChild(h1);
		new_div.appendChild(txt_div);

		new_div.style.position = "absolute";
		new_div.style.top = insertTop.toString() + "px";
		new_div.style.left = insertLeft.toString() + "px";

		addedDivzIndex++;
		new_div.style.zIndex = addedDivzIndex;

		slide.appendChild(new_div);
	}

	function addMathElem() {
		var sel = document.getElementById("paragraph_select_id");

		if(0 === sel.selectedIndex) {

		}
		else if(1 === sel.selectedIndex) {
			poly_div.style.display = "block";
		}
		else if(2 === sel.selectedIndex) {
			matrix_div.style.display = "block";
		}
		else if(4 === sel.selectedIndex) {
			lineq_div.style.display = "block";
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
		addParagraph : addParagraph
	};
}();

