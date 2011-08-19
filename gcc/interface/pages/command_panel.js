//command panel object -- used manipulate the command panel div
var Command_panel = {
    state_main_comm: "hidden",
    state_canvas: "hidden",
	state_groups: "hidden",
    
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
        command_selectTag.setAttribute("onmouseover", "cTooltip.show('select');");
        command_selectTag.setAttribute("onmouseout", "cTooltip.hide();");
        command_selectTag.setAttribute("onclick", "Command_panel.add_groups()");
        command_selectTag.innerHTML = "Select Group";
        
        command_createTag.setAttribute("id", "command_create");
        command_createTag.setAttribute("href", "#");
        command_createTag.setAttribute("onmouseover", "cTooltip.show('create');");
        command_createTag.setAttribute("onmouseout", "cTooltip.hide();");
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

	add_groups: function()
    {
        var command_panelDiv = document.getElementById("command_panel");
        var command_createTag = document.getElementById("command_create");

        var s3Tag = document.createElement("a");
        var d8Tag = document.createElement("a");
        var brTag4 = document.createElement("br");
        brTag4.setAttribute("id", "br4");
		var brTag5 = document.createElement("br");
        brTag5.setAttribute("id", "br5");



        s3Tag.setAttribute("id", "s3");
        s3Tag.setAttribute("href", "#");
        s3Tag.setAttribute("onmouseover", "cTooltip.show('s3');");
        s3Tag.setAttribute("onmouseout", "cTooltip.hide();");
        s3Tag.innerHTML = "S3";
        
        d8Tag.setAttribute("id", "d8");
        d8Tag.setAttribute("href", "#");
        d8Tag.setAttribute("onmouseover", "cTooltip.show('d8');");
        d8Tag.setAttribute("onmouseout", "cTooltip.hide();");
        d8Tag.innerHTML = "D8";
        
        command_panelDiv.insertBefore(s3Tag, command_createTag);
        command_panelDiv.insertBefore(brTag4, command_createTag);
        command_panelDiv.insertBefore(d8Tag, command_createTag);
        command_panelDiv.insertBefore(brTag5, command_createTag);
    },

	remove_groups: function()
    {
        var command_panelDiv = document.getElementById("command_panel");
        var brTag4 = document.getElementById("br4");
        var brTag5 = document.getElementById("br5");
        var s3Tag = document.getElementById("s3");
        var s3Tag = document.getElementById("d8");
        
        command_panelDiv.removeChild(brTag4);
        command_panelDiv.removeChild(brTag5);
        
        command_panelDiv.removeChild(s3Tag);
        command_panelDiv.removeChild(d8Tag);
    },


	
};



var cTooltip=function(){
	var endalpha = 95;
	var alpha = 0;
	var timer = 20;
	var speed = 10;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.select = "Select a predefined group";
	tooltip_map.create = "Create a custom group by specifying type and generators";
	tooltip_map.s3 = "Symmetric group of order 3";
	tooltip_map.d8 = "Dihedral group of order 8";

return{	
	show: function(callee)
	{
		if(tooltip == null)
		{
			tooltip = document.createElement("div");
			tooltip.setAttribute("id","tooltip_id");
		  	var command_panelDiv = document.getElementById("command_panel");
			command_panelDiv.appendChild(tooltip);
			tooltip.style.opacity = 0;
			tooltip.style.filter = 'alpha(opacity=0)';
		}

		tooltip.style.display = "block";
		tooltip.innerHTML = tooltip_map[callee];
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){cTooltip.fade(1)},timer);
	},

	fade: function(d)
	{
		var a = alpha;
		if((a != endalpha && d == 1) || (a != 0 && d == -1))
		{
			var i = speed;
			if(endalpha - a < speed && d == 1){
			i = endalpha - a;
		}
		else if(alpha < speed && d == -1)
		{
			i = a;
		}
		alpha = a + (i * d);
		tooltip.style.opacity = alpha * .01;
		tooltip.style.filter = "alpha(opacity=" + alpha + ")";
		}
		else
		{
			clearInterval(tooltip.timer);
			if(d == -1)
			{
				tooltip.style.display = "none"
			}
		}
	},

	hide: function()
	{
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){cTooltip.fade(-1)},timer);
	}
};
}(); 


var xmlhttp;
 if (window.XMLHttpRequest)
   {// code for IE7+, Firefox, Chrome, Opera, Safari
   xmlhttp=new XMLHttpRequest();
   }
 else
   {// code for IE6, IE5
   xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
   } 
   xmlhttp.open("GET","ajax_info.txt",false);
 	xmlhttp.send();
 	document.getElementById("myDiv").innerHTML=xmlhttp.responseText;

    
