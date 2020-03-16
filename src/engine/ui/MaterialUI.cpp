#pragma once
#include "MaterialUI.h"

MaterialUI::MaterialUI(GLint diffuseTex, glm::vec3 color, GLint maskTex) {
	this->diffuseTex = diffuseTex;
	this->color = color;
	this->maskTex = maskTex;
}

MaterialUI::~MaterialUI() { }

void MaterialUI::sendToShader(Shader &program) {
	program.set1i(diffuseTex,   "material.diffuseTex");
	program.setVec3f(color,		"material.color");
	program.set1i(maskTex,		"material.maskTex");
}