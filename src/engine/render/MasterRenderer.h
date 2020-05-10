#pragma once
#include "../../libs.h"

#include "../shaders/Shader.h"
#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"
#include "../entities/models/Entity.h"
#include "EntityRenderer.h"

class MasterRenderer {
	protected:
		Shader* shader;
		EntityRenderer entityRenderer;
		modelEntity_map entities;

		void sendCamera(Camera &camera);
		void sendFog(Fog &fog);
		void sendLightsPoint(std::vector<LightPoint*> &lightsPoint);


	public:
		MasterRenderer(Shader* shader)
			: shader(shader), entityRenderer(EntityRenderer(shader))
		{ }

		void render(Camera &camera, Fog &fog, std::vector<LightPoint*> &lightsPoint);

		void processEntity(Entity &entity);
};