#pragma once
#include "MasterRenderer.h"

////////////////////////////////////////////////////
////////////// MOVE TO ENTITYRENDERER //////////////
void MasterRenderer::sendCamera(Shader &shader, Camera &camera) {
	shader.setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	shader.setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	shader.setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}

void MasterRenderer::sendFog(Shader &shader, Fog &fog) {
	shader.set1f(fog.getDensity(),  "fog.density");
	shader.set1f(fog.getGradient(), "fog.gradient");
}

void MasterRenderer::sendAmbient(Shader &shader, glm::vec3 &ambient) {
	shader.setVec3f(ambient, "ambient");
}

void MasterRenderer::sendLightsPoint(Shader &shader, std::vector<LightPoint*> &lightsPoint) {
	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		std::string prefix = "lightPoint[" + std::to_string(idx++) + "].";
		shader.setVec3f(lightPoint->getPosition(), (prefix + "position").c_str());
		shader.setVec3f(lightPoint->getColor(),    (prefix + "color").c_str());
		shader.set1f(lightPoint->getIntensity(),   (prefix + "intensity").c_str());
		shader.set1f(lightPoint->getAttenuation(), (prefix + "attenuation").c_str());
		shader.set1f(lightPoint->getFalloffNear(), (prefix + "falloffNear").c_str());
		shader.set1f(lightPoint->getFalloffFar(),  (prefix + "falloffFar").c_str());
	}
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////

void MasterRenderer::sendToShader(Shader& shader, Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	sendCamera(shader, camera);
	sendFog(shader, fog);
	sendAmbient(shader, ambient);
	sendLightsPoint(shader, lightsPoint);
	shader.unuse();
}



void MasterRenderer::reloadShaders() {
	entityRenderer.getShader().reload();
}

void MasterRenderer::render(
	Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint,
	std::vector<Entity*> &entities
) {
	sendToShader(entityRenderer.getShader(), camera, fog, ambient, lightsPoint);

	for (auto *i : entities) {
		entityRenderer.render(i);
	}
}
