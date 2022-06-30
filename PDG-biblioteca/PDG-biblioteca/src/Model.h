#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"

#include "ModelImporter.h"

class ENGINE_API Model : public Entity
{
private:
	bool gammaCorrection;

public:
	Model(Renderer* rend, string const& path, bool flipUVs, bool gamma);
	
	MyModel _myModel;	
	
	void Draw();
};