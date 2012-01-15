
//command panel object -- used manipulate the command panel div
var Command_panel = {
    state_main_comm: "visible",
    state_canvas: "hidden",
	state_groups: "hidden",
	state_create_grp: "hidden",
    
    toggle_panel: function()
    {
        if(this.state_main_comm === "visible")
            this.hide_panel();
        else
            this.show_panel();
            
    },

    show_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Hide Commands Panel");
        var command_panelDiv = document.getElementById("command_panel");
		command_panelDiv.style.display = "block";
        this.state_main_comm = "visible";
    },
    
    hide_panel: function() 
    {
        var togg_button = document.getElementById("toggle_button");
        togg_button.setAttribute("value", "Show Commands Panel");
        var command_panelDiv = document.getElementById("command_panel");
		command_panelDiv.style.display = "none";
        this.state_main_comm = "hidden";
    },

	show_general_commands_panel: function()
	{
		var generalcommand_panelDiv = document.getElementById("general_commands_panel");
		generalcommand_panelDiv.style.display = "block";
	},

	hide_general_commands_panel: function()
	{
        var generalcommand_panelDiv = document.getElementById("general_commands_panel");
		generalcommand_panelDiv.style.display = "none";
	},

	show_group_commands_panel: function()
	{
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
		groupcommand_panelDiv.style.display = "block";
	},

	hide_group_commands_panel: function()
	{
        var groupcommand_panelDiv = document.getElementById("group_commands_panel");
		groupcommand_panelDiv.style.display = "none";
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
        draw_canvasTag.setAttribute("id", "draw_canvas_id");
        draw_canvasTag.setAttribute("class", "scanvas");  


        var finalDiv = document.getElementById("final");
        html_body.insertBefore(draw_canvasTag, finalDiv);
    },
    
    show_main_view: function()
    {
        var canvas_button = document.getElementById("canvas_button");
        canvas_button.setAttribute("value", "Switch to visual mode");
        this.state_canvas = "hidden";
        
        var draw_canvasTag = document.getElementById("draw_canvas_id");
        var html_body = document.getElementById("body_id");
        html_body.removeChild(draw_canvasTag);
        
        var main_viewTag = document.createElement("div");
        main_viewTag.setAttribute("id", "main_view_id");
        main_viewTag.setAttribute("class", "smain_view");  

        var finalDiv = document.getElementById("final");
        html_body.insertBefore(main_viewTag, finalDiv);   
        
    },
    
	add_groups: function()
    {
		if(this.state_groups === "hidden")
		{
			var command_panelDiv = document.getElementById("general_commands_panel");
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
			this.state_groups = "visible";
		}
		else
		{
			this.remove_groups();
		}
    },

	remove_groups: function()
    {
        var command_panelDiv = document.getElementById("general_commands_panel");
        var brTag4 = document.getElementById("br4");
        var brTag5 = document.getElementById("br5");
        var s3Tag = document.getElementById("s3");
        var d8Tag = document.getElementById("d8");
        
        command_panelDiv.removeChild(brTag4);
        command_panelDiv.removeChild(brTag5);
        
        command_panelDiv.removeChild(s3Tag);
        command_panelDiv.removeChild(d8Tag);
		this.state_groups = "hidden";
    },

	add_create_grp_div: function()
	{	
		if(this.state_create_grp === "hidden")
		{
			var command_panelDiv = document.getElementById("general_commands_panel");

			var createGrpDivTag = document.createElement("div");
			createGrpDivTag.setAttribute("id", "grp_div_id");
			createGrpDivTag.setAttribute("onmouseover", "cTooltip.show('generator')");
			createGrpDivTag.setAttribute("onmouseout", "cTooltip.hide()");
			createGrpDivTag.innerHTML="</br>&nbsp;&nbsp;&nbsp;<form onSubmit='return Command_panel.submit_grp()' method='get'>Enter generator: &nbsp;&nbsp;&nbsp;<input type='text' id='generator_id'>&nbsp;&nbsp;&nbsp;<input type='button' value='Add' onclick='Command_panel.add_generator()'>&nbsp;&nbsp;&nbsp;<select id='grp_sel_id' name='Group Type'> <option>Symmetric Group</option></select></br></br>Generators:</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<select id='generators_id' size='5' style='Width:200' ></select>&nbsp;&nbsp;&nbsp;<input type='submit' value='Go'></form></br></br>";
			command_panelDiv.appendChild(createGrpDivTag);
			this.state_create_grp = "visible";
		}
		else
		{
			this.remove_create_grp_div();
		}

	},

	remove_create_grp_div: function()
   {
		var command_panelDiv = document.getElementById("general_commands_panel");
		grp_divTag = document.getElementById("grp_div_id");
		command_panelDiv.removeChild(grp_divTag);
		this.state_create_grp = "hidden";
   },

	add_generator: function()
	{
		var generatorTag = document.getElementById("generator_id");
		var generatorsTag = document.getElementById("generators_id");
		var newgenTag = document.createElement("option");
		newgenTag.innerHTML = generatorTag.value;
		generatorsTag.appendChild(newgenTag);
	},

	static_vars: function()
	{},

	submit_grp: function()
	{
		var generators = new String();
		var generatorsTag = document.getElementById("generators_id");
		for(var geni = 0; geni < generatorsTag.length; geni++)
		{
			 generators += generatorsTag.options[geni].text;
		}
		this.static_vars.generators = generators;
		var group_selTag = document.getElementById("grp_sel_id");
		this.static_vars.group_type = group_selTag.options[group_selTag.selectedIndex].value;

		this.hide_general_commands_panel();
		this.show_group_commands_panel();

		//add to the main div
		var command_panelDiv = document.getElementById("command_panel");
		var group_propertyDiv = document.createElement("div");
		command_panelDiv.appendChild(group_propertyDiv);
		group_propertyDiv.setAttribute("id", "group_property_div_id");
		property_tableTag = document.createElement("table");
		property_tableTag.setAttribute("id", "grp_table_id");
		property_tableTag.setAttribute("border", "1");
		group_propertyDiv.appendChild(document.createElement("br"));
		group_propertyDiv.appendChild(property_tableTag);

		this.add_group_property("Group Type", this.static_vars.group_type);
		this.add_group_property("Group Generators", this.static_vars.generators);
		return false;
	},

	add_group_property: function(property, value)
	{
		var property_tableTag = document.getElementById("grp_table_id")
		rowTag = document.createElement("tr");
		cell1Tag = document.createElement("td");
		cell2Tag = document.createElement("td");
		content1Tag = document.createTextNode(property);
		content2Tag = document.createTextNode(value);
		cell1Tag.appendChild(content1Tag);
		cell2Tag.appendChild(content2Tag);
		rowTag.appendChild(cell1Tag);
		rowTag.appendChild(cell2Tag);
		property_tableTag.appendChild(rowTag);
	},

	goto_general_panel: function()
	{
		this.show_general_commands_panel();
		this.hide_group_commands_panel();
		var group_propertyDiv = document.getElementById("group_property_div_id");
		var command_panelDiv = document.getElementById("command_panel");
		command_panelDiv.removeChild(group_propertyDiv);
	},

	submit_grp_command: function(command)
	{

		var group_types_map = new Object();
		group_types_map["Symmetric Group"] = "SYMMETRIC_GROUP";

		var request = new String();
		var xmlhttp;
		if (window.XMLHttpRequest)
		{// code for IE7+, Firefox, Chrome, Opera, Safari
			xmlhttp=new XMLHttpRequest();
		}
		else
		{// code for IE6, IE5
			xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		} 

		var sessionkeyTag = document.getElementById("session_key_id");

		request = "id=" + sessionkeyTag.value;
		request += "command=" + command;
		request += "param=" + group_types_map[this.static_vars.group_type];
		request	+= this.static_vars.generators;
		xmlhttp.open("GET", request, false);
		xmlhttp.send();
		document.getElementById("main_view_id").innerHTML=xmlhttp.responseText;
	}
	
};





var cTooltip=function(){
	var endalpha = 70;
	var alpha = 0;
	var timer = 20;
	var speed = 10;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.select = "Select a predefined group.";
	tooltip_map.create = "Create a custom group by specifying type and generators.";
	tooltip_map.s3 = "Symmetric group of order 3.";
	tooltip_map.d8 = "Dihedral group of order 8.";
	tooltip_map.generator = "Generators are of the form:</br> 1.For permutation group -- </br> 2.For matrix groups -- </br> 3.For polynomial groups -- .";
	tooltip_map.tutorials = "Visit our tutorial videos on our Youtube page.";
	tooltip_map.source = "Visit the project repository on Google Code.";
	tooltip_map.get_elem = "Compute group elements using Dimono algorithm(permutation groups)."
	tooltip_map.prev_panel = "Go back to the previous panel (cancel ongoing action)."

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


    