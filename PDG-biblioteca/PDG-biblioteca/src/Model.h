#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"

#include "ModelImporter.h"

class ENGINE_API Model : public Entity
{
private:
	
	ModelImporter _importer;

public:
	Model(Renderer* rend, string const& path, bool flipUVs, bool gamma);
	
	MyModel _myModel;

	//vector<meshTexture> textures_loaded;
	//vector<Mesh> meshes;
	//Renderer* _rend;
	
	bool gammaCorrection;
	//bool hasSpecularMaps;
	
	void Draw();
};