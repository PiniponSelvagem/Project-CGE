#pragma once
#include "../../libs.h"

#include "../shaders/Shader.h"
#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../lights/LightPoint.h"
#include "../entities/Entity.h"

#include "UIRenderer.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

class MasterRenderer {
	protected:
		UIRenderer uiRenderer;
		EntityRenderer entityRenderer;
		TerrainRenderer terrainRenderer;
		
	public:
		MasterRenderer(
			const char* uiVertexFile,      const char* uiFragFile,
			const char* entityVertexFile,  const char* entityFragFile,
			const char* terrainVertexFile, const char* terrainFragFiler
		)
		  : uiRenderer(UIRenderer(uiVertexFile, uiFragFile)),
			entityRenderer(EntityRenderer(entityVertexFile, entityFragFile)),
			terrainRenderer(TerrainRenderer(terrainVertexFile, terrainFragFiler))
		{ }
		virtual ~MasterRenderer() { }

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