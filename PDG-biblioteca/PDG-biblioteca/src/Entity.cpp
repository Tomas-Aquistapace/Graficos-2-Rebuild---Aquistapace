#include "Entity.h"
#include <glm/ext/matrix_transform.hpp> 

Entity::Entity(Renderer* renderer)
{
	rend = renderer;

	posVec = vec3(0.0f);
	rotVec = vec3(0.0f);
	scaleVec = vec3(1.0f);

	translateMat = mat4(1.0f);
	rotateXMat = mat4(1.0f);
	rotateYMat = mat4(1.0f);
	rotateZMat = mat4(1.0f);
	scaleMat = mat4(1.0f);
	TRS = mat4(1.0f);
}

void Entity::UpdateTRS()
{
	TRS = translateMat * rotateXMat * rotateYMat * rotateZMat * scaleMat;
}

vec3 Entity::getPosition()
{
	return posVec;
}

void Entity::setPosition(vec3 newPosition)
{
	posVec = newPosition;
	translateMat = translate(mat4(1.0f), posVec);
	UpdateTRS();
}

vec3 Entity::getRotation()
{
	return rotVec;
}

void Entity::setRotationX(float newRotX)
{
	rotVec.x = newRotX;
	vec3 rot;
	rot = vec3(1.0f, 0.0f, 0.0f);
	rotateXMat = rotate(mat4(1.0f), glm::radians(newRotX), rot);
	UpdateTRS();
}

void Entity::setRotationY(float newRotY)
{
	rotVec.y = newRotY;
	vec3 rot;
	rot = vec3(0.0f, 1.0f, 0.0f);
	rotateYMat = rotate(mat4(1.0f), glm::radians(newRotY), rot);
	UpdateTRS();
}

void Entity::setRotationZ(float newRotZ)
{
	rotVec.z = newRotZ;
	vec3 rot;
	rot = vec3(0.0f, 0.0f, 1.0f);
	rotateZMat = rotate(mat4(1.0f), glm::radians(newRotZ), rot);
	UpdateTRS();
}

void Entity::setRotation(vec3 newRot)
{
	vec3 rot;
	if (newRot.x != rotVec.x)
	{
		rotVec.x = newRot.x;
		rot = vec3(1.0f, 0.0f, 0.0f);
		rotateXMat = rotate(mat4(1.0f), glm::radians(newRot.x), rot);
		UpdateTRS();
	}

	if (newRot.y != rotVec.y)
	{
		rotVec.y = newRot.y;
		rot = vec3(0.0f, 1.0f, 0.0f);
		rotateYMat = rotate(mat4(1.0f), glm::radians(newRot.y), rot);
		UpdateTRS();
	}

	if (newRot.z != rotVec.z)
	{
		rotVec.z = newRot.z;
		rot = vec3(0.0f, 0.0f, 1.0f);
		rotateZMat = rotate(mat4(1.0f), glm::radians(newRot.z), rot);
		UpdateTRS();
	}
}

vec3 Entity::getScale()
{
	return scaleVec;
}

void Entity::setScale(vec3 newScale)
{
	scaleVec = newScale;
	scaleMat = scale(mat4(1.0f),scaleVec);
	UpdateTRS();
}