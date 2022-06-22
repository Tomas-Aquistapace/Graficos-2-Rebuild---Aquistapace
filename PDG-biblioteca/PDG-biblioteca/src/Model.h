#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"


class SABASAENGINE_API Model : public Entity
{
public:
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	Renderer* _rend;
	bool gammaCorrection;
	bool hasSpecularMaps;
	Model(Renderer* rend, bool gamma);
	void Draw();
private:
};

