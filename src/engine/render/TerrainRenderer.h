#pragma once
#include "../../libs.h"

#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"
#include "../entities/terrains/Terrain.h"

#include "../shaders/TerrainShader.h"

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