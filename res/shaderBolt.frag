#version 330 core
out vec4 FragColor;

uniform bool boltColour;




void main()
{
   if(!boltColour)
      FragColor = vec4(0.5,0.5,0.5,1);
   else
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
} 