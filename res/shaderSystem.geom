

//Version number
#version 330 core

//Layout qualfier
layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

//Variable from provious stage

in VS_OUT {
    vec2 texCoords;
	vec3 normal;
} VertexIn[];

//Out variable

out VertexData {
    vec2 texCoord1;
	vec3 normal1;
	vec3 lightDir;
	vec3 pos;
} VertexOut;

//Uniforms

uniform mat4 translation;
uniform vec4 direction;
uniform vec4 direction_invert;
uniform vec4 point;





void main()
{


    vec4 aux_direction = direction;
	vec4 aux_direction_invert = direction_invert;
	int counter = 1;
	
	for(int i=0; i < gl_in.length(); i++){
	
		 VertexOut.texCoord1 = VertexIn[i].texCoords;
		 VertexOut.normal1 = vec3(0.0,0.0,0.0);
		 VertexOut.lightDir = vec3(0.0,0.0,0.0);
		 VertexOut.pos = vec3(0.0,0.0,0.0);
		 gl_Position = gl_in[i].gl_Position;
		 EmitVertex();
	}

	 EndPrimitive();

	 for(int i = 0; i < 3; i++){

	     VertexOut.texCoord1 = vec2(-1,-1);
		 VertexOut.normal1 = normalize(VertexIn[i].normal);
	    
		 if(mod(i,2) == 0){

			 for(int j = 0; j < gl_in.length(); j++){
			     
				
		         VertexOut.lightDir = normalize(aux_direction.xyz);
				 VertexOut.lightDir.x = - VertexOut.lightDir.x;
				 gl_Position = gl_in[j].gl_Position + aux_direction*counter;
				 VertexOut.pos = gl_Position.xyz;
			 
				 EmitVertex();
		     }     

			 EndPrimitive();
			 
			 // aux_direction = translation *aux_direction;
			 aux_direction = point + translation * (aux_direction - point);
		     aux_direction[3] = 0; 
	
	      }

		  else{

			 for(int j = 0; j < gl_in.length(); j++){

			     
				 VertexOut.lightDir = normalize(aux_direction_invert.xyz);
				 VertexOut.lightDir.x = - VertexOut.lightDir.x;
				 gl_Position = gl_in[j].gl_Position + aux_direction_invert*counter;
				 VertexOut.pos = gl_Position.xyz;
			 
				EmitVertex();
		     }     
			 
			 EndPrimitive();

			 aux_direction_invert = point + translation * (aux_direction_invert - point);
		     aux_direction_invert[3] = 0;
				
	      }

		  counter++;

	  }
	  
}  