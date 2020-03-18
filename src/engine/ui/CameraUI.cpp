#pragma once
#include "CameraUI.h"

void CameraUI::updateProjectionMatrix() {
	projectionMatrix = glm::ortho(
		0.f, width,
		0.f, height,
		0.f, farPlane
	);

	/*
	float aspectRatio = width / height;

	float aspectRatioWidth = (aspectRatio / 2.f);// *fov;
	float aspectRatioHeight = 0.5f;// *fov;

	projectionMatrix = glm::ortho(
		-aspectRatioWidth, aspectRatioWidth,
		-aspectRatioHeight, aspectRatioHeight,
		0.f, farPlane
	);
	*/
}


CameraUI::CameraUI(float width, float height, float farPlane) {
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
CameraUI::~CameraUI() {
}

const glm::mat4 CameraUI::getViewMatrix() {
	return viewMatrix;
}
const glm::mat4 CameraUI::getProjectionMatrix() {
	return projectionMatrix;
}

void CameraUI::setUIWindowSize(float width, float height) {
	this->width = width;
	this->height = height;
	updateProjectionMatrix();
}
