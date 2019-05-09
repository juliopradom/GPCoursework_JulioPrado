//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

in VertexData {
   vec2 texCoord1;
} Vertex;

//Unfrom variable
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;
 
uniform sampler2D diffuse;

void main()
{
//Setting each vector component to uniform varaible then setting final colour
	//vec4 color;
	//color = vec4(randColourX,randColourY,randColourZ,1.0);

    fragcolor = vec4(texture(diffuse, Vertex.texCoord1));
}