#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 normal;
} gs_in[];



const float MAGNITUDE = 0.4;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123);
}

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
    EmitVertex();
	//float random_variable = random(vec2(gl_in[index].gl_Position.xy));
	//vec4 variable = vec4(gs_in[index].normal, 0.0) * vec4(random_variable, random_variable, random_variable, 0.0 );
	//gl_Position = gl_Position + variable * MAGNITUDE;
	//EmitVertex();
    EndPrimitive();
}

void main()
{
   //float number = random (vec2(gl_in[1].gl_Position.xy));
   //if (number < 0.001f)
    GenerateLine(0); // first vertex normal
	GenerateLine(1);
	GenerateLine(2);
    
}  