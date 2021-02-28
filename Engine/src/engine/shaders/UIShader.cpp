#pragma once
#include <engine/shaders/UIShader.h>


UIShader::UIShader(const char* vertexFile, const char* fragmentFile)
	: Shader(vertexFile, fragmentFile) {
}
UIShader::~UIShader() { }

void UIShader::sendModelMatrix(glm::mat4& modelMatrix) {
	setMat4fv(modelMatrix, "ModelMatrix");
}