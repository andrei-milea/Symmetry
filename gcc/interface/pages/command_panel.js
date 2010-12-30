
//command panel object -- used manipulate the command panel div
var Command_panel = {
    state: "hidden",
    
    toggle_panel: function()
    {
        if(this.state === "visible")
            this.hide_panel();
        else
            this.show_panel();
            
    },
    
    show_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Hide Commands Panel");
        this.state = "visible";
        this.add_commands();
    },
    
    hide_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Show Commands Panel");
        this.state = "hidden";
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
    }
};
    

    
