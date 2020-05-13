#pragma once
#include "../../libs.h"

#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"

#include "../entities/models/Entity.h"

class EntityRenderer {
	private:
		Shader &shader;

		void sendCamera(Camera &camera);
		void sendFog(Fog &fog);
		void sendAmbient(glm::vec3 &ambient);
		void sendLightsPoint(std::vector<LightPoint*> &lightsPoint);

		void bindTexture(Texture* texture, int textureUnit);

	public:
		EntityRenderer(Shader& shader) : shader(shader) { }

		void sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint);

		void render(Entity* entity);

		Shader &getShader() { return shader; }
};