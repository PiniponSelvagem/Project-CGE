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

	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[0]->getPosition(), "light[0].position");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[0]->getColor(), "light[0].color");
	/*
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[0]->getAttenuation(), "light[0].attenuation");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[0]->getFalloffNear(), "light[0].falloffNear");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[0]->getFalloffFar(), "light[0].falloffFar");

	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[1]->getPosition(), "light[1].position");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[1]->getColor(), "light[1].color");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[1]->getAttenuation(), "light[1].attenuation");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[1]->getFalloffNear(), "light[1].falloffNear");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[1]->getFalloffFar(), "light[1].falloffFar");

	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[2]->getPosition(), "light[2].position");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[2]->getColor(), "light[2].color");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[2]->getAttenuation(), "light[2].attenuation");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[2]->getFalloffNear(), "light[2].falloffNear");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[2]->getFalloffFar(), "light[2].falloffFar");

	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[3]->getPosition(), "light[3].position");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[3]->getColor(), "light[3].color");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[3]->getAttenuation(), "light[3].attenuation");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[3]->getFalloffNear(), "light[3].falloffNear");
	shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[3]->getFalloffFar(), "light[3].falloffFar");
	/*
	for (int i = 0; i < 4; ++i) {
		shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[i]->getPosition(), "light[1].position");
		shaders[SHADER_CORE_PROGRAM]->setVec3f(lightsPoint[i]->getColor(), "light[1].color");
		shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[i]->getAttenuation(), "light[1].attenuation");
		shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[i]->getFalloffNear(), "light[1].falloffNear");
		shaders[SHADER_CORE_PROGRAM]->set1i(lightsPoint[i]->getFalloffFar(), "light[1].falloffFar");
	}
	*/
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
}

void Scene::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
	initLights();
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

void Scene::update() {

}
void Scene::render() {
	updateUniforms();
	for (auto *i : models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}
}