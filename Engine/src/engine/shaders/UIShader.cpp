#pragma once
#include <engine/shaders/UIShader.h>

/*
void UIShader::sendCamera(Camera &camera) {
	setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}
*/

void UIShader::sendModelMatrix(glm::mat4& modelMatrix) {
	setMat4fv(modelMatrix, "ModelMatrix");
}