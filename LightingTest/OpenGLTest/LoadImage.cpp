#include "LoadImage.h"
#include "stb_image.h"
#include <iostream>

using namespace std;

LoadTexture::LoadTexture(std::string& name, GLint colorType, unsigned int textureIdx, unsigned int modelType)
{
	m_imageName = name;
	m_colorType = colorType;
	m_textureIdx = textureIdx;
	m_modelType = modelType;
	genTexture();
}

void LoadTexture::genTexture()
{
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	//stbi_set_flip_vertically_on_load(true);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_modelType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_modelType);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = nullptr;
	loadTextureData(&width, &height, &nrChannels, &data);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 
			0, 
			m_colorType,
			width, 
			height, 
			0, 
			m_colorType, 
			GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void LoadTexture::loadTextureData(int* width, int* height, int* nrChannels, unsigned char** data)
{
	std::string imagePath = "../image/";
	imagePath.append(m_imageName);
	(*data) = stbi_load(imagePath.c_str(), width, height, nrChannels, 0);
}

void LoadTexture::useTexture()
{
	glActiveTexture((m_textureIdx == 1) ? GL_TEXTURE0 : GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	
}

void LoadTexture::setTranser(bool isTranvser)
{
	m_bTranvser = isTranvser;
}

