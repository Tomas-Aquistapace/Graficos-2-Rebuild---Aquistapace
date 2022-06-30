#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct MyModel
{
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;

	bool hasSpecularMaps;

	Renderer* renderer;
};

class ENGINE_API ModelImporter
{
private:
	static void processNode(aiNode* node, const aiScene* scene, MyModel& model);
	static Mesh processMesh(aiMesh* mesh, const aiScene* scene, MyModel& model);
	static vector<meshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, MyModel& model);

	static unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);
	
public:
	static void loadModel(string const& path, bool flipUVs, MyModel& model);
};