
//command manager for presentations undo-redo functionality
var PresCmdMng = function () {
	var commands = new Array();
	var idx = 0;
	var draw_cmd_indices = new Array()

	function addCommand() {
		idx++;
		commands[idx] = new Object();
		commands[idx].func = arguments[0];
		commands[idx].args = arguments[1];
	}

	function addDrawCommand() {
		idx++;
		commands[idx] = new Object();
		commands[idx].func = arguments[0];
		commands[idx].args = arguments[1];
		draw_cmd_indices.push(idx);
	}

	function redoDrawCommands() {
		for(var iter = 0; iter < draw_cmd_indices.length; iter++)
			commands[draw_cmd_indices[iter]].func(commands[draw_cmd_indices[iter]].args);
	}

	function rmCommand() {
		idx--;
	}

	function getCommands() {
		return commands;
	}

	function getIdx() {
		return idx;
	}

	//public methods
	return {
		addCommand : addCommand,
		addDrawCommand : addDrawCommand,
		rmCommand : rmCommand,
		redoDrawCommands : redoDrawCommands,
		getCommands : getCommands,
		getIdx : getIdx

	};
}();

	
