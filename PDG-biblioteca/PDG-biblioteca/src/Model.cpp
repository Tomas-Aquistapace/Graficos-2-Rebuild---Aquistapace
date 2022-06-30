#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION

Model::Model(Renderer* rend, string const& path, bool flipUVs, bool gamma) : gammaCorrection(gamma), Entity(rend)
{
	_myModel.renderer = rend;

	_importer.loadModel(path, flipUVs, _myModel);
}

void Model::Draw()
{
	_myModel.renderer->updateProgram(TRS);
	for (unsigned int i = 0; i < _myModel.meshes.size(); i++)
	{
		_myModel.meshes[i].Draw();
	}
}