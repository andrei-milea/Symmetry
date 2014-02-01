
//foreground visualiation for presentarion(slide tranzitions)
var PresVisFg = function () {
	var _scene = null;
	var webgl_context;
	var slides = [];
	var current_slide_idx = 0;

	function nextSlide() {
		if(current_slide_idx < slides.length - 1) {
			slides[current_slide_idx].moveBack();
			current_slide_idx++;
			slides[current_slide_idx].moveFront();
		}
	}

	function prevSlide() {
		if(current_slide_idx > 0) {
			slides[current_slide_idx].moveBack();
			current_slide_idx--;
			slides[current_slide_idx].moveFront();
		}
	}

	function exitVis(elem) {
	}

	function addSlides(slides_data) {
		if(_scene !== null) {
			_scene.clearScene();
		}
		_scene = new Scene();
		_scene.setGl(webgl_context.getGl());
		var slides_data = slides_data.split("slide:");
		slides = [];
		for(var idx = 1; idx < slides_data.length; idx++) {
			var slide = new SlideGeom();
			slide.setSlideData(webgl_context.getGl(), slides_data[idx]);
			_scene.addModel(slide);
			slides.push(slide);
		}
		slides[0].moveFront();
		_scene.setGl(webgl_context.getGl());
		_scene.anim_loop();
	}

	function setGlContext(context) {
		webgl_context = context;
	}

	return {
		setGlContext : setGlContext,
		nextSlide : nextSlide,
		prevSlide : prevSlide,
		exitVis : exitVis,
		addSlides : addSlides
	};
}();

