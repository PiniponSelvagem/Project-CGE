#pragma once
#include "SceneUI.h"


void SceneUI::initUniforms() {
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}

void SceneUI::updateUniforms() {
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}


////////////////////////////////


SceneUI::SceneUI() {
	camera = new CameraUI(800.f, 600.f, 10.f);
}
SceneUI::~SceneUI() {
	delete camera;
	delete shader;
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
}

void SceneUI::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
}

CameraUI* SceneUI::getMainCamera() {
	return camera;
}

void SceneUI::update() {
	//models[0]->changeRotation(glm::vec3(0.f, 0.f, 1.f));
}

void SceneUI::render() {
	glDisable(GL_DEPTH_TEST);
	updateUniforms();
	for (auto *i : models) {
		i->render(shader);
	}
	glEnable(GL_DEPTH_TEST);
}