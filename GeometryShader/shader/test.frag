#version 330 core

out vec4 FragColor;

//in vec3 fColor;

in vec2 TexCoords;

uniform sampler2D person;

void main()
{    
	//FragColor = vec4(fColor, 1.0);
	
	FragColor = texture(person, TexCoords);
}
