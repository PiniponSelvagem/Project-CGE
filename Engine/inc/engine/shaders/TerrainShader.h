#pragma once
#include <engine/shaders/Shader.h>

#include <engine/camera/Camera.h>
#include <engine/enviroment/Fog.h>
#include <engine/lights/LightPoint.h>
#include <engine/terrains/Terrain.h>


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