#pragma once
#include "../../libs.h"

#include "../shaders/Shader.h"
#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"
#include "../entities/models/Entity.h"

#include "EntityRenderer.h"
#include "TerrainRenderer.h"

class MasterRenderer {
	protected:
		EntityRenderer entityRenderer;
		TerrainRenderer terrainRenderer;
		
	public:
		MasterRenderer(Shader* entityShader, Shader* terrainShader)
		  : entityRenderer(EntityRenderer(*entityShader)),
			terrainRenderer(TerrainRenderer(*terrainShader))
		{ }
		virtual ~MasterRenderer() { }

		void reloadShaders();

		void render(
			Camera& camera,
			Fog& fog,
			glm::vec3& ambient,
			std::vector<LightPoint*>& lightsPoint,
			std::vector<Entity*>& entities,
			Terrain& terrain
		);
};