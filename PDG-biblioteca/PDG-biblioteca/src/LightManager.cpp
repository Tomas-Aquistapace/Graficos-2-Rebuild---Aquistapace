#include "LightManager.h"

LightManager::LightManager()
{

}

LightManager::~LightManager()
{
	for (int i = 0; i < _directionals.size(); i++)
	{
		if (_directionals[i] != NULL)
		{
			delete _directionals[i];
			_directionals[i] = NULL;
		}
	}

	for (int i = 0; i < _points.size(); i++)
	{
		if (_points[i] != NULL)
		{
			delete _points[i];
			_points[i] = NULL;
		}
	}

	for (int i = 0; i < _spots.size(); i++)
	{
		if (_spots[i] != NULL)
		{
			delete _spots[i];
			_spots[i] = NULL;
		}
	}
}

void LightManager::addDirectional(Renderer* renderer, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular)
{
	if (_directionals.size() < MAX_DIR_LIGHTS)
	{
		_directionals.push_back(new Lightning(renderer));
		_directionals.back()->initializeDirectional(dir, ambient, diffuse, specular);
	}
}

void LightManager::addPoints(Renderer* renderer, vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, float linear, float quadratic)
{
	if (_points.size() < MAX_POINT_LIGHTS)
	{
		_points.push_back(new Lightning(renderer));
		_points.back()->initializePoint(pos, ambient, diffuse, specular, linear, quadratic);
	}
}

void LightManager::addSpots(Renderer* renderer, vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, float cutOff, float linear, float quadratic)
{
	if (_spots.size() < MAX_DIR_LIGHTS)
	{
		_spots.push_back(new Lightning(renderer));
		_spots.back()->initializeSpot(pos, dir, ambient, diffuse, specular, cutOff, linear, quadratic);
	}
}

void LightManager::removeDirectional(int i)
{
	for (int j = 0; j < _directionals.size(); j++)
	{
		if ((j == i) && _directionals[j] != NULL)
		{
			delete _directionals[j];
			_directionals[j] = NULL;

			_directionals.erase(_directionals.begin() + j);

			return;
		}
	}
}

void LightManager::removePoint(int i)
{
	for (int j = 0; j < _points.size(); j++)
	{
		if ((j == i) && _points[j] != NULL)
		{
			delete _points[j];
			_points[j] = NULL;

			_points.erase(_points.begin() + j);

			return;
		}
	}
}

void LightManager::removeSpot(int i)
{
	for (int j = 0; j < _spots.size(); j++)
	{
		if ((j == i) && _spots[j] != NULL)
		{
			delete _spots[j];
			_spots[j] = NULL;
			
			_spots.erase(_spots.begin() + j);

			return;
		}
	}
}

void LightManager::drawLights()
{
	for (int i = 0; i < _directionals.size(); i++)
	{
		_directionals[i]->draw();
	}

	for (int i = 0; i < _points.size(); i++)
	{
		_points[i]->draw();
	}
	
	for (int i = 0; i < _spots.size(); i++)
	{
		_spots[i]->draw();
	}
}

Lightning* LightManager::getDirectionalLight(int i)
{
	return _directionals[i];
}

Lightning* LightManager::getPointLight(int i)
{
	return _points[i];
}

Lightning* LightManager::getSpotLight(int i)
{
	return _spots[i];
}