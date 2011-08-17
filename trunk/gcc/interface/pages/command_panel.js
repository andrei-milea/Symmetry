
//command panel object -- used manipulate the command panel div
var Command_panel = {
    state_main_comm: "hidden",
    state_canvas: "hidden",
    
    toggle_panel: function()
    {
        if(this.state_main_comm === "visible")
            this.hide_panel();
        else
            this.show_panel();
            
    },
    
    toggle_canvas: function()
    {
        if(this.state_canvas === "visible")
            this.show_main_view();
        else
            this.show_canvas();
    },
    
    show_canvas: function()
    {
        var canvas_button = document.getElementById("canvas_button");
        canvas_button.setAttribute("value", "Switch to text mode");
        this.state_canvas = "visible";
        
        var main_viewTag = document.getElementById("main_view_id");
        var html_body = document.getElementById("body_id");
        html_body.removeChild(main_viewTag);
        
        var draw_canvasTag = document.createElement("canvas");
        draw_canvasTag.setAttribute("id", "draw_canvas");
        draw_canvasTag.setAttribute("class", "scanvas");  
        html_body.appendChild(draw_canvasTag);
    },
    
    show_main_view: function()
    {
        var canvas_button = document.getElementById("canvas_button");
        canvas_button.setAttribute("value", "Switch to visualization mode");
        this.state_canvas = "hidden";
        
        var draw_canvasTag = document.getElementById("draw_canvas");
        var html_body = document.getElementById("body_id");
        html_body.removeChild(draw_canvasTag);
        
        var main_viewTag = document.createElement("div");
        main_viewTag.setAttribute("id", "main_view_id");
        main_viewTag.setAttribute("class", "smain_view");  
        html_body.appendChild(main_viewTag);   
        
    },
    
    
    show_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Hide Commands Panel");
        this.state_main_comm = "visible";
        this.add_commands();
    },
    
    hide_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Show Commands Panel");
        this.state_main_comm = "hidden";
        this.remove_commands();
    },
    
    add_commands: function()
    {
        var command_panelDiv = document.getElementById("command_panel");
        var command_selectTag = document.createElement("a");
        var command_createTag = document.createElement("a");
        var brTag1 = document.createElement("br");
        brTag1.setAttribute("id", "br1");
        var brTag2 = document.createElement("br");
        brTag2.setAttribute("id", "br2");
        
        command_selectTag.setAttribute("id", "command_select");
        command_selectTag.setAttribute("href", "#");
        command_selectTag.innerHTML = "Select Group";
        
        command_createTag.setAttribute("id", "command_create");
        command_createTag.setAttribute("href", "#");
        command_createTag.innerHTML = "Create Group";
        
        command_panelDiv.appendChild(brTag1);
        command_panelDiv.appendChild(command_selectTag);
        command_panelDiv.appendChild(brTag2);
        command_panelDiv.appendChild(command_createTag);
    },
    
    remove_commands: function()
    {
        var command_panelDiv = document.getElementById("command_panel");
        var brTag1 = document.getElementById("br1");
        var brTag2 = document.getElementById("br2");
        var command_selectTag = document.getElementById("command_select");
        var command_createTag = document.getElementById("command_create");
        
        command_panelDiv.removeChild(brTag1);
        command_panelDiv.removeChild(brTag2);
        
        command_panelDiv.removeChild(command_selectTag);
        command_panelDiv.removeChild(command_createTag);
    },

	show_tip: function()
	{
		//TODO -- div inside div ?
        var command_panelDiv = document.getElementById("command_panel");
	}
};
    

    
