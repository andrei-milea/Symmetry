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
	var slidesOldHtml;
	var offY = 0;
	var offX = 0;
	var startY = 0;
	var startX = 0;
	var dragg_width = 0;
	var dragg_height = 0;

	function addSlide() {
		PresCmdMng.addCommand(this.addSlide);

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
		PresCmdMng.addCommand(this.deleteLastSlide);

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

	function editTitle() {
		var title_div = document.getElementById("title_id" + currentSlide.toString());
		if(title_div === undefined || title_div === null) {
			var new_title = document.createElement("div");
			new_title.id = "title_id" + currentSlide.toString();
			new_title.innerHTML = "<div class='title_div'><h1>Edit Slide Title</h1>" +
				"<input type='text' id='title_input_id' size='50' maxlength='100'/> <br/><br/>" +
				"<a href='#' class='fwd_button' onclick='ToolBox.setTitle(); TINY.box.hide()'>Set title</a> </div>";

			TINY.box.show({html:new_title.innerHTML, width:650, height:150, closejs:ToolBox.setTitle});
		}
		else {
			var new_title = document.createElement("div");
			new_title.id = "title_id" + currentSlide.toString();
			var title_text = document.getElementById("title_txt_id_" + currentSlide.toString()).innerText;
	
			new_title.innerHTML = "<div class='title_div'><h1>Edit Slide Title</h1>" +
				"<input type='text' id='title_input_id' size='50' maxlength='100' value='" + title_text + "' /> <br/><br/>" +
				"<a href='#' class='fwd_button' onclick='ToolBox.setTitle(); TINY.box.hide()'>Set title</a> </div>";
			TINY.box.show({html:new_title.innerHTML, width:650, height:150, closejs:ToolBox.setTitle});
		}

	}

	function setTitle() {
		var title_div = document.getElementById("title_id" + currentSlide.toString());
		if(title_div === undefined || title_div === null) {
			title_div = document.createElement("div");
			title_div.id = "title_id" + currentSlide.toString();
			title_div.className = "slide_title";
		}
		var title = document.getElementById("title_input_id").value;
		title_div.innerHTML = "<h1 style='color: white;' id='title_txt_id_" + currentSlide.toString() + "'>" + title + "</h1>";
		var slide = document.getElementById("slide_id_" + currentSlide.toString());
		slide.appendChild(title_div);
	}

	function prevSlide() {
		PresCmdMng.addCommand(this.prevSlide);

		if(currentSlide === 1)
			return;

		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "none";
		currentSlide--;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
		document.getElementById("slide_id_" + currentSlide.toString()).style.display = "block";
	}

	function nextSlide() {
		PresCmdMng.addCommand(this.prevSlide);

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

	function divMove(e) {
		var div = e.target;
		if(div.className !== "draggable") {
			div = e.target.parentNode;
			if(div.className !== "draggable")
				return;
		}

		PresCmdMng.addCommand(divMove, e);
		
		div.style.position = 'absolute';
		div.style.top = (offY + e.clientY - startY) + 'px';
		div.style.left = (offX + e.clientX - startX) + 'px';
	}

	function mouseDown(e){
		var div = e.target;
		if(div.className !== "draggable") {
			div = e.target.parentNode;
			if(div.className !== "draggable")
				return;
		}

		startY = e.clientY;
		startX = e.clientX;
		offY = parseInt(div.style.top);
		offX = parseInt(div.style.left);

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
				var arg = new Object();
				arg.id = div.childNodes[0].id;
				arg.size = Math.min(div.childNodes[0].clientWidth, div.childNodes[0].clientHeight) - 20;
				resizeCanvas(arg);
				PresCmdMng.addDrawCommand(resizeCanvas, arg);
			}
		}	
		
	}

	function resizeCanvas(arg) {
		var div = document.getElementById(arg.id);
		div.childNodes[0].width = arg.size;
		div.childNodes[0].height = arg.size;
		div.childNodes[0].clientWidth = arg.size;
		div.childNodes[0].clientHeight = arg.size;
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

	function addTheme() {
		var math_elems = document.getElementsByClassName("math_elem");
		for(i = 0; i < math_elems.length; i++) {
			math_elems[i].style.background = "#E8E8E8";
		}

		var parag_titles = document.getElementsByClassName("parag_title");
		for(i = 0; i < parag_titles.length; i++) {
			parag_titles[i].style.color = "white";
			parag_titles[i].style.background = "#3333CC";
		}
		var parag_texts = document.getElementsByClassName("parag_text");
		for(i = 0; i < parag_texts.length; i++) {
			parag_texts[i].style.color = "black";
			parag_texts[i].style.background = "#E8E8E8";
		}

		var title_txt = document.getElementById("title_txt_id")
		if(title_txt !== null && title_txt !== undefined) {
			title_txt.style.color = "white";
		}

		var divs = document.getElementsByClassName("draggable");
		for(i = 0; i < divs.length; i++) {
			divs[i].style.border = "none";;
		}
	}

	function preview() {
		var slides_div = document.getElementById("slides_id");
		slidesOldHtml = slides_div.innerHTML;

		addTheme();
		var slides = document.getElementsByClassName("slide_div");
		for(i = 0; i < slides.length; i++) {
			slides[i].style.marginLeft = "20px";
			slides[i].style.marginTop = "1px";
			slides[i].style.border = "1px solid #bbb"
		}
		
		var slidenav = document.getElementById("slidenav_id");
		slidenav.style.marginLeft = "300px";
		slidenav.style.marginTop = "585px";

		var slidesHtml =  slides_div.innerHTML;
		slides_div.innerHTML = "";
		TINY.box.show({html:slidesHtml, animate:true, width:850, height:610, top:1, maskid:'bluemask', opacity: 80,
			   	closejs:ToolBox.restoreSlides});
		setTimeout(PresCmdMng.redoDrawCommands, 800);
	}

	function restoreSlides() {
		var slides = document.getElementById("slides_id");
		slides.innerHTML = slidesOldHtml;
		setTimeout(PresCmdMng.redoDrawCommands, 500);
	}

	function submitPresCommand(command) {
		if(command === "save") {
			var slides_div = document.getElementById("slides_id");
			var pres_name = document.getElementById("pres_name_id").value;
			if(pres_name.length === 0) {
				TINY.box.show({html:'Please enter presentation name!',animate:false,close:false,mask:false,
						boxid:'error',autohide:2,top:-10,left:350});
					return;
			}
			var request = "command=PRESENTATION";
			request += "param=" + command + ":" + pres_name + slides_div.innerHTML.substr(slides_div.innerHTML.indexOf("<"), 
					slides_div.innerHTML.indexOf("<div id=\"slidenav_id\"") - 2);
			var result = submitCommand(request);
			if(-1 !== result.indexOf("Error")) {
				TINY.box.show({html:'Saving Failed!',animate:false,close:false,mask:false,boxid:'error',autohide:2,top:-10,left:350})
				return;
			}
			TINY.box.show({html:result,animate:false,close:false,mask:false,boxid:'success',autohide:2,top:-14,left:-17});
		}
		else if(command === "dir") {
			var request = "command=PRESENTATION";
			request += "param=" + command; 
			var result = submitCommand(request);
			if(-1 !== result.indexOf("Error")) {
				TINY.box.show({html:'Loading presentation list failed!',
						animate:false,close:false,mask:false,boxid:'error',autohide:2,top:-10,left:350});
				return;
			}
			TINY.box.show({html:result, boxid:'frameless', width:500, height:600});
		}
	}

	/////////////////context menu functionality//////////////////////
	function showContextMenu(event) {
		var slideDiv = event.target;
		if("cell" !== slideDiv.style.cursor)
			return;
		var menu = document.getElementById("context_menu_id");
		insertTop = event.clientY - parseInt(slideDiv.offsetTop);
		insertLeft = event.clientX - 50 - parseInt(slideDiv.offsetLeft);
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
		new_div.style.top = insertTop.toString() + "px";
		new_div.style.left = insertLeft.toString() + "px";

		new_div.style.zIndex = addedDivzIndex;

		addedDivzIndex++;

		PresCmdMng.addCommand(slide.appendChild, new_div);

		slide.appendChild(new_div);

		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);

	}

	function addParagraph() {
		var parag_sel = document.getElementById("paragraph_select_id");
		var parag_txt = document.getElementById("paragraph_text_id").value;
		var parag_title = parag_sel.options[parag_sel.selectedIndex].value;

		new_div = document.createElement("div");
		h1 = document.createElement("h1");
		h1.className = "parag_title";
		txt_div = document.createElement("div");
		txt_div.className = "parag_text";
		h1.innerHTML = parag_title;
		txt_div.innerHTML = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + parag_txt + "</br></br>";

		new_div.style.border = "2px groove #6b727c";

		new_div.appendChild(h1);
		new_div.appendChild(txt_div);
		addDraggableDiv(new_div);
	}

	function insertChart(arg) {
		if(arg.type == 0) {
			var ctx = document.getElementById(arg.id).getContext("2d");
			var new_chart = new Chart(ctx);
			new_chart.Pie(arg.data);
		}
		else if(arg.type == 1) {
			var ctx = document.getElementById(arg.id).getContext("2d");
			var new_chart = new Chart(ctx);
			new_chart.Bar(arg.data);
		}
		else if(arg.type == 2) {
			var ctx = document.getElementById(arg.id).getContext("2d");
			var new_chart = new Chart(ctx);
			new_chart.Line(arg.data);
		}
	}

	function addChart(new_div, type, labels, data) {
		var chart = document.getElementById("chart_select_id");
		var labels = document.getElementById("chart_labels_id").value.split(",");
		var datasets = document.getElementById("chart_data_id").value.split(";");
		var title = document.getElementById("chart_title_id").value;
		

		new_div = document.createElement("div");
		new_div.style.border = "2px groove #6b727c";

		addedDivzIndex++;
		var id = "canvas_chart_" + addedDivzIndex.toString();
		new_div.innerHTML =	"<p style='color: #6b727c;'>" + title +
							"</p><canvas id='" + id + "' width='200' height='200' class='scanvas'></canvas>";

		if(chart.selectedIndex == 0) {
			var legend_div = document.createElement("div");
			legend_div.style.width = "200px";
			var data = datasets[0].split(",");
			if(labels.length !== data.length) {
				alert("For each label a numerical value must be provided in the data field.");
				return;
			}
			legend_div.innerHTML = "Legend: <br/>";
			legend_div.style.fontSize = "10px";
			var input = new Array();
			for(i = 0; i < labels.length; i++) {
				input[i] = new Object();
				input[i].value = parseInt(data[i]);
				input[i].color = CSS_COLORS[i % CSS_COLORS.length];
				legend_div.innerHTML += "<p style='margin-top:1px; margin-bottom:1px; background: " + CSS_COLORS[i] + ";'>" + labels[i] + "</p>";
			}

			new_div.appendChild(legend_div);

			addDraggableDiv(new_div);
			var arg = new Object();
			arg.type = 0;	arg.id = id; arg.data = input;
			insertChart(arg);
			PresCmdMng.addDrawCommand(insertChart, arg);
		}	
		else if(chart.selectedIndex == 1) {
			var input = new Object();
			input.labels = labels;
			input.datasets = new Array();
			for(i = 0; i < datasets.length; i++) {
				var data = datasets[i].split(",");
				if(labels.length !== data.length) {
					alert("For each label a numerical value must be provided in the data field.");
					return;
				}
				input.datasets[i] = new Object();
				input.datasets[i].fillColor = CSS_COLORS[i % CSS_COLORS.length];
				input.datasets[i].strokeColor = CSS_COLORS[i % CSS_COLORS.length]; 
				input.datasets[i].data = new Array();
				for(j = 0; j < data.length; j++)
					input.datasets[i].data[j] = data[j];
			}
			
			addDraggableDiv(new_div);
			var arg = new Object();
			arg.type = 1;	arg.id = id; arg.data = input;
			insertChart(arg);
			PresCmdMng.addDrawCommand(insertChart, arg);
		}
		else if(chart.selectedIndex == 2) {
			var input = new Object();
			input.labels = labels;
			input.datasets = new Array();
			for(i = 0; i < datasets.length; i++) {
				var data = datasets[i].split(",");
				if(labels.length !== data.length) {
					alert("For each label a numerical value must be provided in the data field.");
					return;
				}
				input.datasets[i] = new Object();
				input.datasets[i].fillColor = CSS_COLORS[i % CSS_COLORS.length];
				input.datasets[i].strokeColor = CSS_COLORS[i % CSS_COLORS.length]; 
				input.datasets[i].pointColor = CSS_COLORS[i % CSS_COLORS.length]; 
				input.datasets[i].pointStrokeColor = "#fff"; 
				input.datasets[i].data = new Array();
				for(j = 0; j < data.length; j++)
					input.datasets[i].data[j] = data[j];
			}

			addDraggableDiv(new_div);
			var arg = new Object();
			arg.type = 2;	arg.id = id; arg.data = input;
			insertChart(arg);
			PresCmdMng.addDrawCommand(insertChart, arg);
		}
	}

	function addMathElem() {
		var sel = document.getElementById("paragraph_select_id");
		new_div = document.createElement("div");
		new_div.className = "math_elem";
		new_div.style.border = "2px groove #6b727c";

		if(0 === sel.selectedIndex) {
			var canvasDiv = document.createElement("div");
			addedDivzIndex++;
			var idNoStr = addedDivzIndex.toString();
			canvasDiv.setAttribute("id", "canvas_id_" + idNoStr);
			canvasDiv.style.width = "100%";
			canvasDiv.style.height = "100%";
			new_div.appendChild(canvasDiv);
			addDraggableDiv(new_div);

			var fct_area = document.getElementById("fct_area_id");
			var command_input_str = fct_area.value.trim();
			var request = "command=GET_FNC_PLOT";
			if(0 === command_input_str.length) {
				alert("Please provide the function first.");
				return;
			}
			request += "param=" + command_input_str;
			var result = submitCommand(request);
			if(-1 !== result.indexOf("Error")) {
				alert("error : " + result);
				return;
			}

			var arg = new Object();
			arg.points_str = result.substr(6);
			arg.div_id = "canvas_id_" + idNoStr;
			arg.canvas_id = "main_canvas_" + idNoStr;
			PlottingPanel.addPlot(arg);
			PresCmdMng.addDrawCommand(PlottingPanel.addPlot, arg);
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
	}

	///////////////////////////////////////////////////////////////

	//public methods
	return {
		addSlide : addSlide,
		deleteLastSlide : deleteLastSlide,
		editTitle : editTitle,
		setTitle : setTitle,
		preview : preview,
		submitPresCommand : submitPresCommand,
		restoreSlides : restoreSlides,
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
		insertChart : insertChart,
		addChart : addChart,
		addMathElem : addMathElem
	};
}();

