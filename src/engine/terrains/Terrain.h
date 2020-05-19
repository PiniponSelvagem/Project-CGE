#pragma once

#include "../models/Mesh.h"
#include "../models/Texture.h"
#include "TerrainTexturePack.h"

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
				TerrainTexturePack* texturePack, Texture* blendMap)
		: worldPosX(gridX * size), worldPosZ(gridZ * size), SIZE(size), MAX_HEIGHT(maxHeight),
				texturePack(texturePack), blendMap(blendMap) {
			this->mesh = generateTerrain(heightMap);
		}
		virtual ~Terrain() {
			delete blendMap;
			delete mesh;
		}

		inline float getWorldPosX() const { return worldPosX; }
		inline float getWorldPosZ() const { return worldPosZ; }
		inline int getVertexCount() const { return vertexCount; }

		float getHeight(float worldX, float worldZ);

		inline Mesh* getMesh() const { return mesh; }
		inline TerrainTexturePack* getTexturePack() const { return texturePack; }
		inline Texture* getBlendMap() { return blendMap; }
		
		inline glm::mat4 getModelMatrix() const { return modelMatrix; }
};