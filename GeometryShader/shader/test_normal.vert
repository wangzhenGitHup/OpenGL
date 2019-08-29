#version 330 core

//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec3 aColor;

//layout (location = 0) in vec3 aPos;
//layout (location = 2) in vec2 aTexCoords;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT
{
	//vec3 color;
	
	//vec2 texCoords;
	
	vec3 normal;
}vs_out;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	//vs_out.color = aColor;
	//gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	
	//vs_out.texCoords = aTexCoords;
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
	vs_out.normal = vec3(projection * vec4(normalMatrix * aNormal, 0.0));
}