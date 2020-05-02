#pragma once
#include "Model.h"
#include "ObjLoader.h"


Model::Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, Mesh* mesh) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = ovTexDif;
	this->overrideTextureSpecular = ovTexSpec;

	this->mesh = new Mesh(*mesh);
	this->mesh->changePosition(this->position);
	this->mesh->setOrigin(this->position);
}

Model::Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, const char* objFile) {
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = ovTexDif;
	this->overrideTextureSpecular = ovTexSpec;

	std::vector<Vertex> vertex = ObjLoader::loadObj(objFile);
	mesh = new Mesh(
		vertex.data(),
		vertex.size(),
		NULL,
		0,
		glm::vec3(0.f, 0.f, 0.f)
	);

	mesh->changePosition(this->position);
	mesh->setOrigin(this->position);
}

Model::~Model() {
	delete mesh;
}


void Model::render(Shader* shader) {
	material->sendToShader(*shader);

	shader->use();

	overrideTextureDiffuse->bind(0);
	overrideTextureSpecular->bind(1);

	mesh->render(shader);

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}