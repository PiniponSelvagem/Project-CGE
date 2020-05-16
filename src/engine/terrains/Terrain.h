#pragma once

#include "../models/Mesh.h"
#include "../models/Texture.h"
#include "TerrainTexturePack.h"

class Terrain {
	private:
		const float SIZE = 800;
		const int VERTEX_COUNT = 128;

		float worldPosX, worldPosZ;

		Mesh* mesh;
		TerrainTexturePack* texturePack;
		Texture* blendMap;

		glm::mat4 modelMatrix = glm::mat4(1.f);

		Mesh* generateTerrain();



	public:
		Terrain(int gridX, int gridZ, TerrainTexturePack* texturePack, Texture* blendMap)
		: worldPosX(gridX * SIZE), worldPosZ(gridZ * SIZE), texturePack(texturePack), blendMap(blendMap) {
			this->mesh = generateTerrain();
		}
		virtual ~Terrain() {
			delete blendMap;
			delete mesh;
		}

		inline float getWorldPosX() const { return worldPosX; }
		inline float getWorldPosZ() const { return worldPosZ; }
		inline float getVertexCount() const { return VERTEX_COUNT; }

		inline Mesh* getMesh() const { return mesh; }
		inline TerrainTexturePack* getTexturePack() const { return texturePack; }
		inline Texture* getBlendMap() { return blendMap; }
		
		inline glm::mat4 getModelMatrix() const { return modelMatrix; }
};