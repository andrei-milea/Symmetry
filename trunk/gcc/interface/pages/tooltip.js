
var Tooltip = function () {
	var endalpha = 70, alpha = 0, timer = 20, speed = 5;
	var tooltip;
	var tooltip_map = new Object();
	tooltip_map.plotting = "Provide a function or parametric equations separated by comma to obtain a plot. Use small letters(a-z) for the variables. Examples: sin(x)+cos(y); a^2+2*a*b+c; x=t*cos(t), y=t, z=t*sin(t).";
	tooltip_map.discriminant = "Compute the discriminant: $\\Delta = a_n^{2n-2}\\prod_{i < j}(r_i - r_j)^2$, where $r_1, ... r_n$ are the roots(counting multiplicity).";
	tooltip_map.poly = "Insert a polynomial with real or integer coefficients by specifying the degree and adding coefficients starting with the leading term (on the leftmost input field).";
	tooltip_map.roots = "Compute solutions to P(x) = 0.";
	tooltip_map.plot = "Plot the graph of the polynomial.";
	tooltip_map.solveg_lineq = "Solve an underdetermined system (obtain the general solution - $x_{particular}$ + nullspace).";
	tooltip_map.gramsch = "Compute an orthonormal basis given a matrix with linearly independent columns (the Q matrix from the $A = Q R$ factorization using Gram-Schmidt).";
	tooltip_map.mat_rref = "Compute the Row Reduced Echelon Form for the given matrix(Gaussian-Jordan elimination).";
	tooltip_map.sym_codes = "Use the SYMMETRY INTERPRETED LANGUAGE directly in the browser to perform and develop advanced computations using the provided API.";
	tooltip_map.approx_lineq = "Find approximate solutions - if the system is overdetermined - by using the least squares approach.";
	tooltip_map.vecmat = "Insert a vector or a matrix or an expression (in latex syntax) involving operations with both vectors and matrices - a linear combination (an example is provided in the input field).";
	tooltip_map.eigenvalues = "Compute the eigenvalues (if it is a square matrix ($n \\times n$)).";
	tooltip_map.mat_determinant = "Compute the determinant and the trace (if it is a square matrix($n \\times n$)).";
	tooltip_map.norm = "Compute the euclidean norm for the input vector.";
 	tooltip_map.mat_inverse = "Compute the inverse of the matrix ($A^{-1}$) if it is not singular.";
	tooltip_map.lineq = "Enter the system of linear equations by first entering the number of equations ($m$) and unknowns ($n$) and then specifying the coefficients $x_1, x_2, ..., x_n$ and the constant terms $b_1, b_2, ..., b_m$.";
	tooltip_map.solve_lineq = "Solve the linear system if it has a single uniques solution.";
	tooltip_map.generator = "Generators should be provided as a permutation array $(x_1,x_2,x_3,...)$ which represents the permutation 1->$x_1$, 2->$x_2$, 3->$x_3$, ...";
	tooltip_map.get_elem = "Compute the elements of the group.";
	tooltip_map.get_center = "Compute the Center subgroup (elements that commute with all the elements of the group).";
	tooltip_map.get_cgraph = "Compute the Cayley graph of the group (colored directed graph).";
	tooltip_map.get_rel = "Compute the defining relations of the group.";

return{	
	show: function (callee)
	{
		if(tooltip == null)
		{
			tooltip = document.createElement("div");
			tooltip.setAttribute("id","tooltip_id");
			var command_panelDiv = document.getElementById("computations_panel");
			command_panelDiv.appendChild(tooltip);
			tooltip.style.opacity = 0;
			tooltip.style.filter = 'alpha(opacity=0)';
		}
		
		if(tooltip.offsetTop < window.scrollY)
		{
			tooltip.style.top=(window.scrollY + 370).toString() + "px";
		}
		if(tooltip.offsetTop + tooltip.offsetHeight > window.scrollY + 650)
		{
			tooltip.style.top=(window.scrollY + 370).toString() +"px";
		}

		tooltip.style.display = "block";
		tooltip.innerHTML = tooltip_map[callee];
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){Tooltip.fade(1)},timer);
		MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
	},

	fade: function (d)
	{
		var a = alpha;
		if((a !== endalpha && d === 1) || (a !== 0 && d === -1))
		{
			var i = speed;
			if(endalpha - a < speed && d === 1){
			i = endalpha - a;
		}
		else if(alpha < speed && d === -1)
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
			if(d === -1)
			{
				tooltip.style.display = "none";
			}
		}
	},

	hide: function ()
	{
		clearInterval(tooltip.timer);
		tooltip.timer = setInterval(function(){Tooltip.fade(-1)},timer);
	}
};
}(); 
    
