#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"

class ENGINE_API Model : public Entity
{
private:
	
public:
	Model(Renderer* rend, bool gamma);
	
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	Renderer* _rend;
	
	bool gammaCorrection;
	bool hasSpecularMaps;
	
	void Draw();
};