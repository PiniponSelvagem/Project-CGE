#pragma once
#include "Camera.h"

#define MAX_PITCH 89.9f	// Supported range: [0, 89.9]. Values outside this range might have unexpected behavior.

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
			position += glm::normalize(up * glm::vec3(0.f, 1.f, 0.f)) * movementSpeed * dTime;
			break;
		case DOWN:
			position -= glm::normalize(up * glm::vec3(0.f, 1.f, 0.f)) * movementSpeed * dTime;
			break;
	}
}

void Camera::updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY) {
	pitch += static_cast<GLfloat>(offsetY) * sensivity * dTime;
	yaw += static_cast<GLfloat>(offsetX) * sensivity * dTime;

	if (pitch > MAX_PITCH)
		pitch = MAX_PITCH;
	else if (pitch < -MAX_PITCH)
		pitch = -MAX_PITCH;

	if (yaw > 360.f || yaw < -360.f)
		yaw = 0.f;
}