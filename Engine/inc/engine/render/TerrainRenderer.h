#pragma once
#include <engine/Libs.h>

#include <engine/camera/Camera.h>
#include <engine/enviroment/Fog.h>
#include <engine/lights/LightPoint.h>
#include <engine/terrains/Terrain.h>

#include <engine/shaders/TerrainShader.h>

class TerrainRenderer {
	private:
		TerrainShader shader;

		void bindTextures(Terrain& terrain);

	public:
		TerrainRenderer(const char* vertexFile, const char* fragFile)
		: shader(TerrainShader(vertexFile, fragFile)) { }

		void sendToShader(Camera& camera, Fog& fog, glm::vec3& ambient, std::vector<LightPoint*>& lightsPoint);

		void render(Terrain& terrain);

		void reloadShader() { shader.reload(); }
};