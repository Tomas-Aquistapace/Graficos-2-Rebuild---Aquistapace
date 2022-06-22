#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION

Model::Model(Renderer* rend, bool gamma) : gammaCorrection(gamma), Entity(rend)
{
	_rend = rend;
}
void Model::Draw() {
	rend->updateProgram(TRS);
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
}
