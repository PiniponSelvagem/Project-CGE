#pragma once
#include "MasterRenderer.h"


void MasterRenderer::reloadShaders() {
	entityRenderer.getShader().reload();
}

void MasterRenderer::render(
	Camera& camera, Fog& fog, glm::vec3& ambient, std::vector<LightPoint*>& lightsPoint,
	std::vector<Entity*>& entities
) {
	entityRenderer.sendToShader(camera, fog, ambient, lightsPoint);

	for (auto *i : entities) {
		entityRenderer.render(i);
	}
}
