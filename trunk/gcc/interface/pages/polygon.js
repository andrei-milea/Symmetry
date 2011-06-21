function Polygon()
{
    var vertices = [];
    var verticesNum;
    var vertexSize;
        
return  {

    load: function(vertSize, vertNum, vert)   {
        
        verticesNum = vertNum;
        vertexSize = vertSize;
        
        //check size
        if(verticesNum * vertexSize !== vertices.length)
        {
            throw
            {
                name: "PolygonSizeError",
                message: "Invalid number of vertices"
            }
        }
        
        vertices = vert[0];
    },
    
    
    getVerticesNum: function()    {
        return verticesNum;
    },
    
    getVertexSize: function()    {
        return vertexSize;
    },
    
    getVerticesAsFloat32: function()  {
        return Float32Array(vertices);
    }
}
}