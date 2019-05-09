//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

in VertexData {
   vec2 texCoord1;
   vec3 normal1;
   vec3 lightDir;
   vec3 pos;
} Vertex;

//Uniform variables

uniform mat4 projection;
 
uniform sampler2D diffuse;

void main()
{

	if(Vertex.texCoord1[0] == -1){   //It is not the sun

	
	    
		vec3 n = Vertex.normal1;   
		vec3 p = normalize(inverse(projection) * vec4(Vertex.pos,0)).xyz;         
	                    
		vec3 v = - p;  

		float vdn = 0.4 - max(dot(v, n), 0.0);        // the rim contribution
	
		float intensity;
		vec4 color;
		intensity = dot(Vertex.lightDir,  - Vertex.normal1);

		

		if (intensity > 0.0)
		   color = vec4(0.2 + 0.8*intensity, 0.1 + 0.4*intensity, 0.1 + 0.4*intensity, 1.0);
		else
		   color = vec4(0.2,0.1,0.1,1.0);

	  fragcolor.a = 0.4;
	  fragcolor.rgb = vec3(smoothstep(0.4, 0.8, vdn)) + vec3(color.x,color.y,color.z);
	  
	  
	   
	}

	else {
	   fragcolor = vec4(texture(diffuse, Vertex.texCoord1));
	}

}