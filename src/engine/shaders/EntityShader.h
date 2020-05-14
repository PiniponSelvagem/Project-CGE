#pragma once
#include "Shader.h"

#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"
#include "../entities/models/Material.h"


class EntityShader : public Shader {
	public:
		EntityShader(const char* vertexFile, const char* fragmentFile)
			: Shader(vertexFile, fragmentFile)
		{ }
		virtual ~EntityShader() { }

		void sendCamera(Camera& camera);
		void sendFog(Fog& fog);
		void sendAmbient(glm::vec3& ambient);
		void sendLightsPoint(std::vector<LightPoint*>& lightsPoint);
		
		void sendMaterial(Material& material);

		void sendModelMatrix(glm::mat4& modelMatrix);
};