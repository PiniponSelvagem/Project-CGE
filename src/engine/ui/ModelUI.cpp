#pragma once
#include "ModelUI.h"


ModelUI::ModelUI(glm::vec3 position, MaterialUI* material, Texture* ovTexDif, Texture* ovTexMask, std::vector<Mesh*> meshes) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = ovTexDif;
	this->overrideTextureMask = ovTexMask;

	// Range-for --- C++11
	for (auto *i : meshes) {
		this->meshes.push_back(new Mesh(*i));
	}

	for (auto &i : this->meshes) {
		i->changePosition(this->position);
		i->setOrigin(this->position);
	}
}

ModelUI::~ModelUI() {
	for (auto *&i : meshes) {
		delete i;
	}
}

void ModelUI::changeRotation(const glm::vec3 rotation) {
	for (auto &i : meshes) {
		i->changeRotation(rotation);
	}
}
void ModelUI::changePosition(const glm::vec3 position) {
	for (auto &i : meshes) {
		i->changePosition(position);
	}
}

void ModelUI::render(Shader* shader) {
	material->sendToShader(*shader);

	shader->use();

	for (auto &i : meshes) {
		overrideTextureDiffuse->bind(0);
		overrideTextureMask->bind(1);

		i->render(shader);
	}

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}