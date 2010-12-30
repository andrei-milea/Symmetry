

//normalized matrix used to compute rotations in 3d space
function RotationMatrix()
{
    var mat11, mat12, mat13,
        mat21, mat22, mat23,
        mat31, mat32, mat33;
        
return  {

    identity: function()   {
        mat11 = 1;  mat12 = 0;  mat13 = 0;
        mat21 = 0;  mat22 = 1;  mat23 = 0;
        mat31 = 0;  mat32 = 0;  mat33 = 1;
    },
    
    multiply: function(rot_mat)    {
        mat11 = mat11 * rot_mat.mat11 + mat12 * rot_mat.mat21 + mat13 * rot_mat.mat31;
        mat12 = mat11 * rot_mat.mat21 + mat12 * rot_mat.mat22 + mat13 * rot_mat.mat23;
        mat13 = mat11 * rot_mat.mat31 + mat12 * rot_mat.mat32 + mat13 * rot_mat.mat33;
        mat21 = mat21 * rot_mat.mat11 + mat22 * rot_mat.mat21 + mat23 * rot_mat.mat31;
        mat22 = mat21 * rot_mat.mat21 + mat22 * rot_mat.mat22 + mat23 * rot_mat.mat23;
        mat23 = mat21 * rot_mat.mat31 + mat22 * rot_mat.mat32 + mat23 * rot_mat.mat33;
        mat31 = mat31 * rot_mat.mat11 + mat32 * rot_mat.mat21 + mat33 * rot_mat.mat31;
        mat32 = mat31 * rot_mat.mat21 + mat32 * rot_mat.mat22 + mat33 * rot_mat.mat23;
        mat33 = mat31 * rot_mat.mat31 + mat32 * rot_mat.mat32 + mat33 * rot_mat.mat33;
    },
    
    //inertial space to object space (normal multiplication)
    rotateVector: function(vec3d)   {
        return new Vector3d(
                            mat11 * vec3d.x + mat21 * vec3d.y + mat31 * vec3d.z,
                            mat12 * vec3d.x + mat22 * vec3d.y + mat32 * vec3d.z,
                            mat13 * vec3d.x + mat23 * vec3d.y + mat33 * vec3d.z);
    }
    
};

}

//4*3 matrix to perform rotations + translations
function Transform3dMatrix()
{
    var mat11, mat12, mat13,
        mat21, mat22, mat23,
        mat31, mat32, mat33,
        tx,     ty,     tz;         //translation
        
return  {
    
    identity: function()   {
        mat11 = 1;  mat12 = 0;  mat13 = 0;
        mat21 = 0;  mat22 = 1;  mat23 = 0;
        mat31 = 0;  mat32 = 0;  mat33 = 1;
        
        tx = 0; ty = 0; tx = 0;
    },
    
    zeroTranslation: function() {
        tx = 0; ty = 0; tz = 0;
    },
    
    setTranslation: function(vec3d)   {
        this.identity();
        
        tx = vec3d.x;
        ty = vec3d.y;
        tz = vec3d.z;    
    },
    
    getTranslation: function()    {
        return Vector3d(tx, ty, tz);
    },
    
    //set the amount of rotation around an arbitrary axis
    //theta is an angle given in radians
    //the arbitrary axis must pass through the origin
    setRotation: function(vec3daxis, theta)  {
        var sin_theta = Math.sin(theta);
        var cost_theta = Math.cos(theta);
        
        var ax = (1 - cost_theta)* vec3daxis.x;
        var ay = (1 - cost_theta)* vec3daxis.y;
        var az = (1 - cost_theta)* vec3daxis.z;
        
        mat11 = ax * vec3daxis.x + cost_theta;
        mat12 = ax * vec3daxis.y + vec3daxis.z * sin_theta;
        mat13 = ax * vec3daxis.z - vec3daxis.y *sin_theta;
        
        mat21 = ay * vec3daxis.x - vec3daxis.z * sin_theta;
        mat22 = ay * vec3daxis.y + cost_theta;
        mat23 = ay * vec3daxis.z + vec3daxis.z * sin_theta;
        
        mat31 = az * vec3daxis.x + vec3daxis.y * sin_theta;
        mat32 = az * vec3daxis.y - vec3daxis.x * sin_theta;
        mat33 = az * vec3daxis.z + cost_theta;    
    },
    
    //get RotationMatrix from the Transform3dMatrix
    getRotationMatrix: function()   {
        var rot_mat = new RotationMatrix();
        rot_mat.m11 = mat11;  rot_mat.m12 = mat12;  rot_mat.m13 = mat13;
        rot_mat.m21 = mat21;  rot_mat.m22 = mat22;  rot_mat.m23 = mat23;
        rot_mat.m31 = mat31;  rot_mat.m32 = mat32;  rot_mat.m33 = mat33;
        return rot_mat;    
    },
    
    setScale: function(vec3dscale)    {
        this.identity();
        mat11 = vec3dscale.x;
        mat22 = vec3dscale.y;
        mat23 = vec3dscale.z;
        tz = 1;                
    },
    
    //setup the matrix to perform a rotation about an
    //arbitrary plane through the origin
    setReflection: function(vec3dplane) {
        this.zeroTranslation();
        
        var ax = -2 * vec3dplane.x;
        var ay = -2 * vec3dplane.y;
        var az = -2 * vec3dplane.z;
        
        mat11 = 1 + ax * vec3dplane.x;
        mat22 = 1 + ay * vec3dplane.y;
        mat32 = 1 + az * vec3dplane.z;
        
        mat12 = mat21 * ax * vec3dplane.y;
        mat13 = mat31 * ax * vec3dplane.z;
        mat23 = mat32 * ay * vec3dplane.z;
    },
    
    inverse: function()   {
    //TODO
    
    },
    
    determinant: function()    {
    //TODO
    
    }
};
    
}

//4*4 matrix to perform 