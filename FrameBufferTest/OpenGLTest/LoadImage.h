#ifndef __LOAD__IMAGE__H__
#define __LOAD__IMAGE__H__

#include <glad/glad.h>
#include <string>

class LoadTexture
{
public:
	LoadTexture(std::string& name, GLint colorType, unsigned int textureIdx, unsigned int modelType = GL_REPEAT);
	void useTexture();
	void setTranser(bool isTranvser);

private:
	void loadTextureData(int* width, int* height, int* nrChannels, unsigned char** data);
	void genTexture();

private:
	std::string m_imageName;
	unsigned int m_textureId;
	GLint m_colorType;
	bool m_bTranvser;
	unsigned int m_textureIdx;
	unsigned int m_modelType;
};


#endif