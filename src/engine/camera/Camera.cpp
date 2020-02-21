#pragma once
#include "Camera.h"

Camera::Camera(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction) {
	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	this->position = position;

	this->pitch = direction.x;
	this->yaw   = direction.y;
	this->roll  = direction.z;
}

Camera::~Camera() {
}

const glm::mat4 Camera::getViewMatrix() {
	updateCameraVectors();
	viewMatrix = glm::lookAt(position, position + front, up);
	return viewMatrix;
}
const glm::mat4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}
const glm::vec3 Camera::getPosition() {
	return position;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}