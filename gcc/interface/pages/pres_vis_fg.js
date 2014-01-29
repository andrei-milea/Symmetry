
//foreground visualiation for presentarion(slide tranzitions)
var PresVisFg = function () {
	var _scene = null;
	var webgl_context;

	function nextSlide() {
	}

	function prevSlide() {
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
		for(var idx = 1; idx < slides_data.length; idx++) {
			var slide = new SlideGeom();
			slide.setSlide(webgl_context.getGl(), slides_data[idx]);
			_scene.addModel(slide);
		}
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

