#pragma once
#include <engine/models/Mesh.h>
#include <engine/models/Texture.h>
#include <engine/terrains/TerrainTexturePack.h>

class Terrain {
	private:
		float SIZE;
		float MAX_HEIGHT;
		const float MAX_PIXEL_COLOR = 256 * 256 * 256;

		float worldPosX, worldPosZ;
		int vertexCount = 0;
		std::vector<std::vector<float>> heights;

		Mesh* mesh;
		TerrainTexturePack* texturePack;
		Texture* blendMap;

		glm::mat4 modelMatrix = glm::mat4(1.f);

		Mesh* generateTerrain(const char* heightMap);

		float getHeightOfHMap(unsigned x, unsigned z, unsigned char *hMap, unsigned imgWidth, unsigned channels);
		glm::vec3 calcNormal(unsigned x, unsigned z, unsigned char *hMap, unsigned imgWidth, unsigned channels);

		float getVertexHeight(float x, float z);


	public:
		Terrain(int gridX, int gridZ,
				const char* heightMap, float size, float maxHeight,
				TerrainTexturePack* texturePack, Texture* blendMap);
		virtual ~Terrain();

		float getWorldPosX();
		float getWorldPosZ();
		int getVertexCount();

		float getHeight(float worldX, float worldZ);

		Mesh* getMesh();
		TerrainTexturePack* getTexturePack();
		Texture* getBlendMap();
		
		glm::mat4 getModelMatrix();
};