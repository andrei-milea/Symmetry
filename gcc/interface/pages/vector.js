
//class used to represent 3 dimensional vector
//and provide common vector operations
function Vector3d(_x, _y, _z)   {
    var x = _x,
        y = _y,
        z = _z;
        
return  {
    
    isEqual: function(vec3d)   {
        if((vec3d.x === this.x) && (vec3d.y === this.y) && (vec3d.z === this.z))
        {
            return true;
        }
        else
        {
            return false;
        }
            
    },
    
    add: function(vec3d)   {
        x += vec3d.x;
        y += vec3d.y;
        z += vec3d.z;
    },
    
    multiply: function(scalar)  {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    },
    
    norm: function()    {
        return Math.sqrt(x*x + y*y + z*z);
    },
    
    normalize: function()   {
        if(0 === this.norm())
        {
            return;
        }
        else
        {
            x *= 1 / this.norm();
            y *= 1 / this.norm();
            z *= 1 / this.norm();
        }            
    },
    
    crossProduct: function(vec3d)   {
        return Vector3d(y*vec3d.z - z*vec3d.y, z*vec3d.x - x*vec3d.z, x*vec3d.y - y*vec3d.x);
    },
    dotProduct: function(vec3d)   {
        return x*vec3d.x + y*vec3d.y + z*vec3d.z;    
    },
    
    distance: function(vec3d)   {
        var dx = x - vec3d.x;
        var dy = y - vec3d.y;
        var dz = z - vec3d.z;
        return Math.sqrt(dx*dx + dy*dy + dz*dz);
    
    }
};   

}
