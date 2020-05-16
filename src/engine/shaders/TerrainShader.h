#pragma once
#include "Shader.h"

#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../lights/LightPoint.h"
#include "../terrains/Terrain.h"


class TerrainShader : public Shader {
	public:
		TerrainShader(const char* vertexFile, const char* fragmentFile)
			: Shader(vertexFile, fragmentFile)
		{ }
		virtual ~TerrainShader() { }

		void sendCamera(Camera& camera);
		void sendFog(Fog& fog);
		void sendAmbient(glm::vec3& ambient);
		void sendLightsPoint(std::vector<LightPoint*>& lightsPoint);
		
		void sendTerrainData(Terrain& terrain);

		void sendModelMatrix(glm::mat4& modelMatrix);

};