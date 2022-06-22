#include "Camera.h"


Camera::Camera(Renderer* rend)
{
	_renderer = rend;
	_position = glm::vec3(-1.0f, 0.0f, 0.0f);
	_target = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera(){

}

void Camera::setTransform(){
	_renderer->updateView(_position,_front,up);
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
	setTransform();
}

glm::vec3 Camera::getPosition() {
	return _position;
}

void Camera::setTarget(glm::vec3 target) {
	_target = target;
	setTransform();
}
void Camera::setFront(glm::vec3 front) {
	_front = front;
	setTransform();
}

glm::vec3 Camera::getTarget() {
	return _target;
}
glm::vec3 Camera::getFront() {
	return _front;
}

void Camera::moveOnWorld(glm::vec3 movement)
{
	_position += movement;
	setTransform();
}

void Camera::moveOnLocal(glm::vec3 movement)
{
	glm::vec3 dir = (movement.x * side) + (movement.y * _front) + (movement.z * up);

	_position += dir;
	setTransform();
}

void Camera::rotate(glm::vec3 movement)
{
	yaw += movement.x;
	pitch += movement.y;
	roll += movement.z;

	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front = glm::normalize(_front);
	
	up.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch + 90.0f));
	up.y = sin(glm::radians(pitch + 90.0f));
	up.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch + 90.0f));

	side = glm::cross(_front, up);

	setTransform();
}