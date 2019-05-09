//Version Number
#version 400

//The layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

//Out variable

out VS_OUT {
    vec2 texCoords;
	vec3 normal;
} vs_out;

//Uniform variables


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;



void main()
{
	//Assigning the texture coordinates and normal

	vs_out.texCoords = VertexTexCoord;
	vs_out.normal = normalize(mat3(transpose(inverse(model))) * VertexNormal);

	// Sets the position of the current vertex
	gl_Position = projection * view * model * vec4(VertexPosition, 1.0);
	
}