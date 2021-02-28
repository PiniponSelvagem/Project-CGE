#pragma once
#include <engine/render/MasterRenderer.h>


MasterRenderer::MasterRenderer(
	const char* uiVertexFile,      const char* uiFragFile,
	const char* entityVertexFile,  const char* entityFragFile,
	const char* terrainVertexFile, const char* terrainFragFiler
) : uiRenderer(UIRenderer(uiVertexFile, uiFragFile)),
	entityRenderer(EntityRenderer(entityVertexFile, entityFragFile)),
	terrainRenderer(TerrainRenderer(terrainVertexFile, terrainFragFiler)) {
}

MasterRenderer::~MasterRenderer() { }

void MasterRenderer::reloadShaders() {
	uiRenderer.reloadShader();
	entityRenderer.reloadShader();
	terrainRenderer.reloadShader();
}

void MasterRenderer::render(
	std::vector<UI*>& uis,
	Camera& camera, Fog& fog, glm::vec3& ambient, std::vector<LightPoint*>& lightsPoint,
	std::vector<Entity*>& entities, Terrain& terrain
) {
	entityRenderer.sendToShader(camera, fog, ambient, lightsPoint);
	terrainRenderer.sendToShader(camera, fog, ambient, lightsPoint);

	terrainRenderer.render(terrain);

	for (auto *i : entities) {
		entityRenderer.render(i);
	}

	uiRenderer.render(uis);
}
