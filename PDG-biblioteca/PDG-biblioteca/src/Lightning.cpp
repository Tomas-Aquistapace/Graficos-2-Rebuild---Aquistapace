#include "Lightning.h"

int Lightning::dirLights = 0;
int Lightning::pointLights = 0;
int Lightning::spotLights = 0;

Lightning::Lightning(Renderer* rend) 
{
	_rend = rend;

	_pos = glm::vec3(0.0f);
	_dir = glm::vec3(0.0f);
	_constant = 1.0f;
	_linear = 0.0f;
	_quadratic = 0.0f;
	_cutOff = 0.0f;
	_active = false;

	_color = glm::vec3(0.4f);
}

void Lightning::initializePoint(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float linear, float quadratic)
{
	_lightType = point;
	id = pointLights++;

	_pos = pos;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_constant = 1.0f;
	_linear = linear;
	_quadratic = quadratic;
	_active = true;

	_color = glm::vec3(0.4f);
}

void Lightning::initializeDirectional(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_lightType = directional;
	id = dirLights++;

	_dir = dir;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_active = true;

	_color = glm::vec3(0.4f);
}

void Lightning::initializeSpot(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float linear, float quadratic)
{
	_lightType = spot;
	id = spotLights++;

	_pos = pos;
	_dir = dir;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_cutOff = cutOff;
	_constant = 1.0f;
	_linear = linear;
	_quadratic = quadratic;
	_active = true;

	_color = glm::vec3(0.4f);
}

// -------------------------

void Lightning::setPos(glm::vec3 newPos)
{
	_pos = newPos;
}

void Lightning::setDir(glm::vec3 newDir)
{
	_dir = newDir;
}

void Lightning::setActiveState(bool newActiveState)
{
	_active = newActiveState;
}

void Lightning::setColor(float r, float g, float b)
{
	_color = glm::vec3(r, g, b);
}

void Lightning::draw()
{
	_rend->updateLight(_pos, _dir, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _cutOff, static_cast<unsigned int>(_lightType), _active, id, _color);
}

// -------------------------

bool Lightning::getActiveState()
{
	return _active;
}

glm::vec3 Lightning::getDir()
{
	return _dir;
}

glm::vec3 Lightning::getPos() 
{
	return _pos;
}