#pragma once
#include "TestUI.h"

void TestUI::initShaders() {
	// SHADER_CORE_PROGRAM
	shader = new Shader("resources/shaders/vertex_gui.glsl", "resources/shaders/fragment_gui.glsl");
}
void TestUI::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_mask.png", GL_TEXTURE_2D));
}
void TestUI::initMaterials() {
	materials.push_back(new MaterialUI(
		TEX_CRATE,
		glm::vec3(1.f, 0.f, 0.f), TEX_CRATE_MASK
	));
}
void TestUI::initModels() {
	/*
	std::vector<Mesh*> meshes;

	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(100.f)
		)
	);

	models.push_back(new ModelUI(
		glm::vec3(100.f, 100.f, -1.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_MASK],
		meshes
	));

	models.push_back(new ModelUI(
		glm::vec3(125.f, 125.f, -2.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE_MASK],
		textures[TEX_CRATE_MASK],
		meshes
	));

	for (auto *&i : meshes) {
		delete i;
	}
	*/
}


////////////////////////////////


TestUI::TestUI() : SceneUI() {
}
TestUI::~TestUI() {
}

void TestUI::update() {
	//models[0]->changeRotation(glm::vec3(0.f, 0.f, 1.f));
}
