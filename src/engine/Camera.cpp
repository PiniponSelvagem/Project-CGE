#pragma once
#include "Camera.h"

void Camera::updateCameraVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}



Camera::Camera(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction, bool is3D) {
	this->is3D = is3D;

	//viewMatrix = glm::mat4(1.f);
	projectionMatrix = glm::mat4(1.f);

	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;;

	this->position = position;
	this->right = glm::vec3(0.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);

	pitch = 0.f;
	yaw = -90.f;
	roll = 0.f;

	movementSpeed = 3.f;
	sensivity = 5.f;
	
	updateCameraVectors();
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

void Camera::updateProjectionMatrix(float aspectRatio) {
	if (is3D) {
		projectionMatrix = glm::perspective(
			glm::radians(fov),
			aspectRatio,
			nearPlane, farPlane
		);
	}
	else {
		// TODO: axis should be changed so camera does not move like in prespective view, but only along the X and Z axis (maybe Y should be a fixed value???)
		float aspectRatioWidth = (aspectRatio / 2.f) * fov;
		float aspectRatioHeight = 0.5f * fov;
		projectionMatrix = glm::ortho(
			-aspectRatioWidth, aspectRatioWidth,
			-aspectRatioHeight, aspectRatioHeight,
			nearPlane, farPlane
		);
	}
}

void Camera::move(const float &dTime, const int direction) {
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

void Camera::updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY) {
	pitch += static_cast<GLfloat>(offsetY) * sensivity * dTime;
	yaw += static_cast<GLfloat>(offsetX) * sensivity * dTime;

	if (pitch > 80.f)
		pitch = 80.f;
	else if (pitch < -80.f)
		pitch = -80.f;

	if (yaw > 360.f || yaw < -360.f)
		yaw = 0.f;

	//std::cout << "pitch: " << pitch << " yaw: " << yaw << std::endl;
}
void Camera::updateInput(const float &dTime, const int direction, const double &offsetX, const double &offsetY) {
	updateMouseInput(dTime, offsetX, offsetY);
}