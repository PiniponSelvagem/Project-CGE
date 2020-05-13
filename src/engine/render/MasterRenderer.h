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
		EntityRenderer entityRenderer;
		
	public:
		MasterRenderer(Shader* shader) : entityRenderer(EntityRenderer(*shader)) { }
		virtual ~MasterRenderer() { }

		void reloadShaders();

		void render(
			Camera &camera,
			Fog &fog,
			glm::vec3 &ambient,
			std::vector<LightPoint*> &lightsPoint,
			std::vector<Entity*> &entities
		);
};