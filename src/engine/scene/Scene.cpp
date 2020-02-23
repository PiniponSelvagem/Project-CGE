#include "Scene.h"

enum shader_enum {
	SHADER_CORE_PROGRAM
};

void Scene::initUniforms() {
	//TODO: more generic shader selection???
	int SHADER_CORE_PROGRAM = 0;

	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(*lights[0], "lightPos0");
}

void Scene::updateUniforms() {
	//TODO: more generic shader selection???
	int SHADER_CORE_PROGRAM = 0;

	// Update viewMatrix (camera)
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(camera->getPosition(), "cameraPos");
	camera->updateProjectionMatrix();
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");

}



Scene::Scene() { }
Scene::~Scene() {
	delete camera;

	for (size_t i = 0; i < shaders.size(); ++i)	  { delete shaders[i]; }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i]; }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (size_t i = 0; i < lights.size(); ++i)    { delete lights[i]; }
}

void Scene::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
	initLights();
}

Camera* Scene::getMainCamera() {
	return camera;
}

void Scene::render() {
	//TODO: more generic shader selection???
	int SHADER_CORE_PROGRAM = 0;

	updateUniforms();
	for (auto *i : models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}
}