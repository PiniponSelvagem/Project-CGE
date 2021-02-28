#pragma once
#include <engine/Libs.h>

#include <engine/shaders/Shader.h>
#include <engine/camera/Camera.h>
#include <engine/enviroment/Fog.h>
#include <engine/lights/LightPoint.h>
#include <engine/entities/Entity.h>

#include <engine/render/UIRenderer.h>
#include <engine/render/EntityRenderer.h>
#include <engine/render/TerrainRenderer.h>

class MasterRenderer {
	protected:
		UIRenderer uiRenderer;
		EntityRenderer entityRenderer;
		TerrainRenderer terrainRenderer;
		
	public:
		MasterRenderer(
			const char* uiVertexFile, const char* uiFragFile,
			const char* entityVertexFile, const char* entityFragFile,
			const char* terrainVertexFile, const char* terrainFragFiler
		);
		virtual ~MasterRenderer();

		void reloadShaders();

		void render(
			std::vector<UI*>& uis,
			Camera& camera,
			Fog& fog,
			glm::vec3& ambient,
			std::vector<LightPoint*>& lightsPoint,
			std::vector<Entity*>& entities,
			Terrain& terrain
		);
};