#pragma once
#include <engine/camera/Camera3D.h>

Camera3D::Camera3D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction)
	: Camera(fov, nearPlane, farPlane, position, direction) {

	//viewMatrix = glm::mat4(1.f);
	projectionMatrix = glm::mat4(1.f);

	this->right = glm::vec3(0.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);

	movementSpeed = 3.f;
	sensivity = 5.f;

	updateCameraVectors();
}
Camera3D::~Camera3D() { }

void Camera3D::updateProjectionMatrix() {
	projectionMatrix = glm::perspective(
		glm::radians(fov),
		aspectRatio,
		nearPlane, farPlane
	);
}