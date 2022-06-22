#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Model.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);

class SABASAENGINE_API modelImporter
{
private:
	string directory;
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<meshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

public:
	~modelImporter();
	vector<Model*> models_Loaded;
	void loadModel(string const& path, bool flipUVs, Renderer* rend);
};

