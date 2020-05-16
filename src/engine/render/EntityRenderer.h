#pragma once
#include "../../libs.h"

#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../lights/LightPoint.h"
#include "../entities/Entity.h"

#include "../shaders/EntityShader.h"

class EntityRenderer {
	private:
		EntityShader shader;

		void bindTexture(Texture* texture, int textureUnit);

	public:
		EntityRenderer(const char* vertexFile, const char* fragFile)
		: shader(EntityShader(vertexFile, fragFile)) { }

		void sendToShader(Camera& camera, Fog& fog, glm::vec3& ambient, std::vector<LightPoint*>& lightsPoint);

		void render(Entity* entity);

		void reloadShader() { shader.reload(); }
};