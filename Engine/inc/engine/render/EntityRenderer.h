#pragma once
#include <engine/Libs.h>

#include <engine/camera/Camera.h>
#include <engine/enviroment/Fog.h>
#include <engine/lights/LightPoint.h>
#include <engine/entities/Entity.h>

#include <engine/shaders/EntityShader.h>

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