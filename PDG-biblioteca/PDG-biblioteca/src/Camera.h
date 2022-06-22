#pragma once
#include "Exports.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Renderer.h"

class SABASAENGINE_API Camera
{
protected:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 side = glm::vec3(0.0f);
	float pitch = 0.0f;
	float yaw = -90.0f;
	float roll = 0.0f;
	Renderer* _renderer;
public:
	Camera(Renderer* rend);
	~Camera();
	void setTransform();
	void setPosition(glm::vec3 position);
	void setFront(glm::vec3 front);
	void setTarget(glm::vec3 position);
	glm::vec3 getPosition();
	glm::vec3 getFront();
	void moveOnWorld(glm::vec3 movement);
	void moveOnLocal(glm::vec3 movement);
	void rotate(glm::vec3 movement);
	glm::vec3 getTarget();
};

