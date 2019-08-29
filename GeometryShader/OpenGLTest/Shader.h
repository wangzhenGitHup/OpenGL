#ifndef __SHADER__H__
#define __SHADER__H__

#include<glad/glad.h>
#include<string>
#include<fstream>
#include <sstream>
#include<iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value)const;
	void setFloat(const std::string& name, float value)const;
	void setFloat4(const std::string& name, float value1, float value2, float value3, float value4);
	void setMat4(const std::string& name, glm::mat4 matrix);
	void setVec3(const std::string& name, float value1, float value2, float value3);
	void setVec3(const std::string& name, glm::vec3& value);
	unsigned int getShaderPrograme(){ return m_shaderProgramID; }

private:
	unsigned int m_shaderProgramID;
};

#endif