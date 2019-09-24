#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D depthMap;
uniform float nearPlane;
uniform float farPlane;


float linearDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main()
{   
	float depthValue = texture(depthMap, TexCoords).r;
	FragColor = vec4(vec3(depthValue), 1.0);
}
