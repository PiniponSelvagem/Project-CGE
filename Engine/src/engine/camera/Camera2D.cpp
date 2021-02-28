#pragma once
#include <engine/camera/Camera2D.h>

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
Camera2D::~Camera2D() { }

void Camera2D::updateProjectionMatrix() {
	float aspectRatioWidth = (aspectRatio / 2.f) * fov;
	float aspectRatioHeight = 0.5f * fov;

	projectionMatrix = glm::ortho(
		-aspectRatioWidth, aspectRatioWidth,
		-aspectRatioHeight, aspectRatioHeight,
		nearPlane, farPlane
	);
}