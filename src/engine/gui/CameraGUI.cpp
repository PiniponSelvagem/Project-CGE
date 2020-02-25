#include "CameraGUI.h"

void CameraGUI::updateProjectionMatrix() {
	projectionMatrix = glm::ortho(
		0.f, width,
		0.f, height,
		0.f, farPlane
	);
}


CameraGUI::CameraGUI(float width, float height, float farPlane) {
	this->width = width;
	this->height = height;
	this->farPlane = farPlane;

	viewMatrix = glm::lookAt(
		glm::vec3(0.f, 0.f, 0.f),	// position
		glm::vec3(0.f, 0.f, -1.f),	// position + front
		glm::vec3(0.f, 1.f, 0.f)	// up
	);

	projectionMatrix = glm::mat4(1.f);

	updateProjectionMatrix();
}
CameraGUI::~CameraGUI() {
}

const glm::mat4 CameraGUI::getViewMatrix() {
	return viewMatrix;
}
const glm::mat4 CameraGUI::getProjectionMatrix() {
	return projectionMatrix;
}

void CameraGUI::setGuiSize(float width, float height) {
	this->width = width;
	this->height = height;
	updateProjectionMatrix();
}
