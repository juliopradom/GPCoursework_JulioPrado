#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

out VS_OUT {
   vec3 normal;
} vs_out;




uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vs_out.normal = normalize(mat3(transpose(inverse(model))) * VertexNormal);
	gl_Position = projection * view * model * vec4(VertexPosition, 1.0);
}