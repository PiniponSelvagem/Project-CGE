#pragma once
#include "MasterRenderer.h"


void MasterRenderer::reloadShaders() {
	entityRenderer.reloadShader();
	terrainRenderer.reloadShader();
}

void MasterRenderer::render(
	Camera& camera, Fog& fog, glm::vec3& ambient, std::vector<LightPoint*>& lightsPoint,
	std::vector<Entity*>& entities, Terrain& terrain
) {
	entityRenderer.sendToShader(camera, fog, ambient, lightsPoint);
	terrainRenderer.sendToShader(camera, fog, ambient, lightsPoint);

	terrainRenderer.render(terrain);

	for (auto *i : entities) {
		entityRenderer.render(i);
	}
}
