#pragma once
#include "Model.h"
#include "ObjLoader.h"


Model::Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, std::vector<Mesh*> meshes) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = ovTexDif;
	this->overrideTextureSpecular = ovTexSpec;

	// Range-for --- C++11
	for (auto *i : meshes) {
		this->meshes.push_back(new Mesh(*i));
	}

	for (auto &i : this->meshes) {
		i->changePosition(this->position);
		i->setOrigin(this->position);
	}
}

Model::Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, const char* objFile) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = ovTexDif;
	this->overrideTextureSpecular = ovTexSpec;

	std::vector<Vertex> mesh = ObjLoader::loadObj(objFile);
	meshes.push_back(
		new Mesh(
			mesh.data(),
			mesh.size(),
			NULL,
			0,
			glm::vec3(0.f, 0.f, 0.f)
		)
	);

	for (auto &i : meshes) {
		i->changePosition(this->position);
		i->setOrigin(this->position);
	}
}

Model::~Model() {
	for (auto *&i : meshes) {
		delete i;
	}
}

void Model::changeRotation(const glm::vec3 rotation) {
	for (auto &i : meshes) {
		i->changeRotation(rotation);
	}
}
void Model::changePosition(const glm::vec3 position) {
	for (auto &i : meshes) {
		i->changePosition(position);
	}
}


void Model::render(Shader* shader) {
	material->sendToShader(*shader);

	shader->use();

	for (auto &i : meshes) {
		overrideTextureDiffuse->bind(0);
		overrideTextureSpecular->bind(1);

		i->render(shader);
	}

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}