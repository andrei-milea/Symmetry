//toolbox
var ToolBox = function () {
	var slideNo = 1;
	var currentSlide = 1;

	function addSlide() {
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNo++;
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
	}

	function deleteSlide() {
		if(slideNo === 1)
			return;
		if(currentSlide === slideNo)
			currentSlide--;
		slideNo--;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
	}

	function prevSlide() {
		if(currentSlide === 1)
			return;

		currentSlide--;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
	}

	function nextSlide() {
		if(currentSlide === slideNo)
			return;

		currentSlide++;
		var slideNoTxt = document.getElementById("slide_no_id");
		slideNoTxt.defaultValue = currentSlide.toString() + "/" + slideNo.toString();
	}
	function onCursorChange(sel) {
		var slides = document.getElementsByClassName("slide_div");
		if("Move" == sel.options[sel.selectedIndex].value) {
			for(i = 0; i < slides.length; i++)
				slides[i].style.cursor = "pointer";
		}
		else {
			for(i = 0; i < slides.length; i++)
				slides[i].style.cursor = "cell";
		}
	}

	function preview() {
	}

	function save() {
	}

	//public methods
	return {
		addSlide : addSlide,
		deleteSlide : deleteSlide,
		preview : preview,
		save : save,
		prevSlide : prevSlide,
		nextSlide : nextSlide,
		onCursorChange : onCursorChange
	};
}();

