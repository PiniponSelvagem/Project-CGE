#pragma once
#include "Camera.h"

void Camera::updateCameraVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}



Camera::Camera(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction) {
	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	this->position = position;

	this->yaw   = direction.x;
	this->pitch = direction.y;
	this->roll  = direction.z;
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

void Camera::setAspectRatio(float aspectRatio) {
	this->aspectRatio = aspectRatio;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}
void Camera::moveFly(const float &dTime, const int direction) {
	switch (direction) {
		case FORWARD:
			position += front * movementSpeed * dTime;
			break;
		case BACKWARD:
			position -= front * movementSpeed * dTime;
			break;
		case LEFT:
			position -= right * movementSpeed * dTime;
			break;
		case RIGHT:
			position += right * movementSpeed * dTime;
			break;
		case UP:
			position += up * movementSpeed * dTime;
			break;
		case DOWN:
			position -= up * movementSpeed * dTime;
			break;
	}
}
void Camera::moveWalk(const float &dTime, const int direction) {
	switch (direction) {
		case FORWARD:
			position += glm::normalize(front * glm::vec3(1.f, 0.f, 1.f)) * movementSpeed * dTime;
			break;
		case BACKWARD:
			position -= glm::normalize(front * glm::vec3(1.f, 0.f, 1.f)) * movementSpeed * dTime;
			break;
		case LEFT:
			position -= right * movementSpeed * dTime;
			break;
		case RIGHT:
			position += right * movementSpeed * dTime;
			break;
		case UP:
			position += worldUp * movementSpeed * dTime;
			break;
		case DOWN:
			position -= worldUp * movementSpeed * dTime;
			break;
	}
}

void Camera::changePanTilt(const double &offsetX, const double &offsetY) {
	pitch += static_cast<GLfloat>(offsetY) * sensivity * BASE_SENSIVITY;
	yaw += static_cast<GLfloat>(offsetX) * sensivity * BASE_SENSIVITY;

	setPitch(pitch);
	setYaw(yaw);
}