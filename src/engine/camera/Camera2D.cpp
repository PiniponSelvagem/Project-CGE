#pragma once
#include "Camera.h"

void Camera2D::updateCameraVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}



Camera2D::Camera2D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction)
	: Camera(fov, nearPlane, farPlane, position, direction) {

	//viewMatrix = glm::mat4(1.f);
	projectionMatrix = glm::mat4(1.f);

	this->right = glm::vec3(0.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);

	movementSpeed = 3.f;
	sensivity = 5.f;

	updateCameraVectors();
}

Camera2D::~Camera2D() {
}

void Camera2D::updateProjectionMatrix(float aspectRatio) {
	float aspectRatioWidth = (aspectRatio / 2.f) * fov;
	float aspectRatioHeight = 0.5f * fov;

	projectionMatrix = glm::ortho(
		-aspectRatioWidth, aspectRatioWidth,
		-aspectRatioHeight, aspectRatioHeight,
		nearPlane, farPlane
	);
}

void Camera2D::move(const float &dTime, const int direction) {
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

void Camera2D::updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY) {
	pitch += static_cast<GLfloat>(offsetY) * sensivity * dTime;
	yaw += static_cast<GLfloat>(offsetX) * sensivity * dTime;

	if (pitch > 80.f)
		pitch = 80.f;
	else if (pitch < -80.f)
		pitch = -80.f;

	if (yaw > 360.f || yaw < -360.f)
		yaw = 0.f;
}