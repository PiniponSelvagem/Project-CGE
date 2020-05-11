#pragma once
#include "MasterRenderer.h"

void MasterRenderer::sendCamera(Camera* camera) {
	shader->use();

	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setVec3f(camera->getPosition(), "cameraPos");
	camera->updateProjectionMatrix();
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");

	shader->unuse();
}

void MasterRenderer::sendFog(Fog* fog) {
	shader->use();

	shader->set1f(fog->getDensity(),  "fog.density");
	shader->set1f(fog->getGradient(), "fog.gradient");

	shader->unuse();
}

void MasterRenderer::sendAmbient(glm::vec3 ambient) {
	shader->use();

	shader->setVec3f(ambient, "ambient");

	shader->unuse();
}

void MasterRenderer::sendLightsPoint(std::vector<LightPoint*> lightsPoint) {
	shader->use();

	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		std::string prefix = "lightPoint[" + std::to_string(idx++) + "].";
		shader->setVec3f(lightPoint->getPosition(), (prefix + "position").c_str());
		shader->setVec3f(lightPoint->getColor(),    (prefix + "color").c_str());
		shader->set1f(lightPoint->getIntensity(),   (prefix + "intensity").c_str());
		shader->set1f(lightPoint->getAttenuation(), (prefix + "attenuation").c_str());
		shader->set1f(lightPoint->getFalloffNear(), (prefix + "falloffNear").c_str());
		shader->set1f(lightPoint->getFalloffFar(),  (prefix + "falloffFar").c_str());
	}

	shader->unuse();
}
