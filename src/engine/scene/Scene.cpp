#pragma once
#include "Scene.h"

enum shader_enum {
	SHADER_CORE_PROGRAM
};

void Scene::initUniforms() {
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}

void Scene::updateUniforms() {
	// Update viewMatrix (camera)
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(camera->getPosition(), "cameraPos");
	
	fog->sendToShader(*shaders[SHADER_CORE_PROGRAM]);

	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		lightPoint->sendToShader(*shaders[SHADER_CORE_PROGRAM], idx++);
	}	

	camera->updateProjectionMatrix();
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}


////////////////////////////////


Scene::Scene() { }
Scene::~Scene() {
	delete camera;

	for (size_t i = 0; i < shaders.size(); ++i)	  { delete shaders[i];   }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (size_t i = 0; i < lightsPoint.size(); ++i) { delete lightsPoint[i]; }
	delete fog;
}

void Scene::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
	initLights();
	initEnviroment();
}

void Scene::reloadShader() {
	std::cout << "SHADER: reloading started..." << std::endl;
	for (auto *i : shaders) {
		i->reload();
	}
	std::cout << "SHADER: reload complete" << std::endl;
}

Camera* Scene::getMainCamera() {
	return camera;
}

void Scene::update(float dTime) {

}
void Scene::render() {
	updateUniforms();
	for (auto *i : models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}
}