var DihedralRep = function() {
	var _scene = null;
	var _polygon = null;

	var webgl_context;
	
	function setGlContext(context) {
		webgl_context = context;
	}

	function startAnim(size) {
		if(_scene !== null) {
			_scene.clearScene();
		}
		_scene = new Scene();
		_polygon = new Polygon();
		_scene.setGl(webgl_context.getGl());
		addPolygonToScene(size);
		_scene.anim_loop();
	}	

	function addPolygonToScene(size) {
		if(size < 3 || size > 9)
			return;
		_polygon.init(0, 50);
		Letters.init();
		
		for(i = 1; i <= size; i++) {
			var x = 2.3 * Math.cos(2 * Math.PI * i / size);
			var y = 2.3 * Math.sin(2 * Math.PI * i / size);
			_polygon.vertices.push(x);		//x coordintate
			_polygon.vertices.push(y);		//y coordinate
			_polygon.vertices.push(0);		//z coordinate
			var letter_weight = 0.152;
			var letter_height = 0.21;
			if(i < 10) {
				var rotx = x * 0.8;
				var roty = y * 0.8;
				x = x * 1.1;
				y = y * 1.1;
				_polygon.textCoords.push(x + letter_weight/2);
				_polygon.textCoords.push(y + letter_height/2);
				_polygon.textCoords.push(0);

				_polygon.textCoords.push(x - letter_weight/2);
				_polygon.textCoords.push(y + letter_height/2);
				_polygon.textCoords.push(0);

				_polygon.textCoords.push(x + letter_weight/2);
				_polygon.textCoords.push(y - letter_height/2);
				_polygon.textCoords.push(0);
				
				_polygon.textCoords.push(x-letter_weight/2);
				_polygon.textCoords.push(y - letter_height/2);
				_polygon.textCoords.push(0);

				_polygon.rottextCoords.push(rotx + letter_weight/2);
				_polygon.rottextCoords.push(roty + letter_height/2);
				_polygon.rottextCoords.push(0);

				_polygon.rottextCoords.push(rotx - letter_weight/2);
				_polygon.rottextCoords.push(roty + letter_height/2);
				_polygon.rottextCoords.push(0);

				_polygon.rottextCoords.push(rotx + letter_weight/2);
				_polygon.rottextCoords.push(roty - letter_height/2);
				_polygon.rottextCoords.push(0);
				
				_polygon.rottextCoords.push(rotx-letter_weight/2);
				_polygon.rottextCoords.push(roty - letter_height/2);
				_polygon.rottextCoords.push(0);

				_polygon.addTextureCoords(Letters.pos[size - i + 1]);
				_polygon.blacktextureCoords.push(1,1);
			}
		}
		_polygon.setVertexNum(size);
		_scene.addModel(_polygon);
	}

	function rotatePolygon() {
		_polygon.Rotate();
	}

	function reflectPolygon() {
		_polygon.Reflect();
	}

	function isPendingMove() {
		return _polygon.isPendingMove();
	}

	return {
		startAnim : startAnim,
		rotatePolygon : rotatePolygon,
		reflectPolygon : reflectPolygon,
		isPendingMove : isPendingMove,
		setGlContext : setGlContext
	}
}();

