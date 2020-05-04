#pragma once
#include "Scene.h"

Scene::Scene() { }
Scene::~Scene() {
	delete camera;

	delete masterRenderer;
	delete entityRenderer;
	for (size_t i = 0; i < shaders.size(); ++i)	  { delete shaders[i];   }
	for (auto *&i : meshes) { delete i; }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (auto *&i : entities) { delete i; }
	for (size_t i = 0; i < lightsPoint.size(); ++i) { delete lightsPoint[i]; }
	delete fog;
}

void Scene::initScene() {
	initShaders();
	initMeshes();
	initTextures();
	initMaterials();
	initModels();
	initEntities();
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
	masterRenderer->sendCamera(camera);
	masterRenderer->sendFog(fog);
	masterRenderer->sendLightsPoint(lightsPoint);

	for (auto *i : entities) {
		entityRenderer->render(i);
	}
}