#ifndef __MODEL__H__
#define __MODEL__H__

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"

class Shader;

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}

	void Draw(Shader shader);

private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType textureType, std::string typeName);

public:
	/*  Model Data */
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;
};

#endif