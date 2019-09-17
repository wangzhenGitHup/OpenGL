#version 330 core

out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 Texcoords;
}fs_in;

uniform sampler2D floorTex;

uniform vec3 lightPos[4];
uniform vec3 lightColors[4];
uniform bool gamma;
uniform vec3 viewPos;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor);

void main()
{   
	vec3 texColor = texture(floorTex, fs_in.Texcoords).rgb;
	
	vec3 lightColor = vec3(0.0);
	
	for(int i = 0; i < 4; i++)
	{
		lightColor += BlinnPhong(normalize(fs_in.Normal), fs_in.FragPos, lightPos[i], lightColors[i]);
	}
	
	texColor *= lightColor;
	
	if(gamma)
	{
		texColor = pow(texColor, vec3(1.0 / 2.2));
	}
	
	FragColor = vec4(texColor, 1.0);
}

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor)
{
	vec3 lightDir = normalize(lightPos - fragPos);
	
	float diff = max(0.0, dot(lightDir, normal));
	
	vec3 diffuse = diff * lightColor;
	
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	
	
	vec3 halfDir = normalize(viewDir + lightDir);
	
	float spec = pow(max(0.0, dot(halfDir, normal)), 64.0);
	
	vec3 specular = spec * lightColor;
	
	float distance = length(lightPos - fragPos);
	
	float attenuation = 1.0 / (gamma ? distance * distance : distance);
	
	diffuse *= attenuation;
	specular *= attenuation;
	
	return diffuse + specular;
}