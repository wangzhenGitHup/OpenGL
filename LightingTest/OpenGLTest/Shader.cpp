#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR:SHADER::FILE_NOT_SUCCESS_READ" << std::endl;
	}
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
	}

	//片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMILE_FAILED\n" << infoLog << std::endl;
	}

	m_shaderProgramID = glCreateProgram();
	glAttachShader(m_shaderProgramID, vertex);
	glAttachShader(m_shaderProgramID, fragment);
	glLinkProgram(m_shaderProgramID);

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgramID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(m_shaderProgramID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgramID, name.c_str()), value);
}

void Shader::setFloat4(const std::string& name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_shaderProgramID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setMat4(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setVec3(const std::string& name, float value1, float value2, float value3)
{
	glUniform3f(glGetUniformLocation(m_shaderProgramID, name.c_str()), value1, value2, value3);
}

void Shader::setVec3(const std::string& name, glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_shaderProgramID, name.c_str()), 1, &value[0]);
}
