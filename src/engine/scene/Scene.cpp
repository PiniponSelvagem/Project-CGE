#pragma once
#include "Scene.h"

Scene::Scene() { }
Scene::~Scene() {
	delete camera;

	delete masterRenderer;
	delete terrain;
	for (auto *&i : terrainTexPacks) { delete i; }
	for (auto *&i : meshes) { delete i; }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (auto *&i : entities) { delete i; }
	for (size_t i = 0; i < lightsPoint.size(); ++i) { delete lightsPoint[i]; }
	delete fog;
}

void Scene::initScene() {
	initRenderer();
	initMeshes();
	initTextures();
	initMaterials();
	initModels();
	initEntities();
	initLights();
	initEnviroment();
	initCamera();
}

void Scene::reloadShader() {
	std::cout << "SHADER: reloading started..." << std::endl;
	masterRenderer->reloadShaders();
	std::cout << "SHADER: reload complete" << std::endl;
}

Camera* Scene::getMainCamera() {
	return camera;
}

void Scene::render() {
	masterRenderer->render(
		*camera, *fog, ambient, lightsPoint,
		entities, *terrain
	);
}