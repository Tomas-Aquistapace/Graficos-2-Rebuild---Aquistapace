#pragma once
#include <vector>
#include "Exports.h"
#include "Lightning.h"
#include "Renderer.h"

using namespace std;
using namespace glm;

#define MAX_DIR_LIGHTS 6
#define MAX_POINT_LIGHTS 6
#define MAX_SPOT_LIGHTS 6

class ENGINE_API LightManager
{
private:
	vector<Lightning*> _directionals;
	vector<Lightning*> _points;
	vector<Lightning*> _spots;

public:
	LightManager();
	~LightManager();

	void addDirectional(Renderer* renderer, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular);
	void addPoints(Renderer* renderer, vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, float linear, float quadratic);
	void addSpots(Renderer* renderer, vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, float cutOff, float linear, float quadratic);

	void removeDirectional(int i);
	void removePoint(int i);
	void removeSpot(int i);

	void drawLights();

	Lightning* getDirectionalLight(int i);
	Lightning* getPointLight(int i);
	Lightning* getSpotLight(int i);
};

