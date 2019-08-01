#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shining;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
};

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform vec3 viewPos;
uniform Material material;

//定向光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

//点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//聚光灯
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{   
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 finalColor = CalcDirLight(dirLight, normal, viewDir);
	finalColor += CalcPointLight(pointLight, normal, FragPos, viewDir);
	finalColor = CalcSpotLight(spotLight, normal, FragPos, viewDir);
	
	FragColor = vec4(finalColor, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	//漫反射光
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shining);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	//环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//漫反射光
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	//环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shining);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	//计算衰减度
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//漫反射光
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	//环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shining);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	//计算衰减度
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	//计算点光源强度
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
	ambient *= attenuation;
	diffuse *= intensity * attenuation;
	specular *= intensity * attenuation;
	
	return (ambient + diffuse + specular);
}