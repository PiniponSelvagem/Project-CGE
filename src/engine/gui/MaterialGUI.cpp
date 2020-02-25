#pragma once
#include "MaterialGUI.h"

MaterialGUI::MaterialGUI(GLint diffuseTex, glm::vec3 color, GLint maskTex) {
	this->diffuseTex = diffuseTex;
	this->color = color;
	this->maskTex = maskTex;
}

MaterialGUI::~MaterialGUI() { }

void MaterialGUI::sendToShader(Shader &program) {
	program.set1i(diffuseTex,   "material.diffuseTex");
	program.setVec3f(color,		"material.color");
	program.set1i(maskTex,		"material.maskTex");
}