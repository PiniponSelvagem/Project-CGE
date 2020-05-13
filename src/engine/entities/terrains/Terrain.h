#pragma once

#include "../models/Mesh.h"
#include "../models/Texture.h"

class Terrain {
	private:
		const float SIZE = 800;
		const int VERTEX_COUNT = 128;

		float worldPosX, worldPosZ;

		Mesh* mesh;
		Texture* texture;
		glm::mat4 modelMatrix = glm::mat4(1.f);

		Mesh* generateTerrain();



	public:
		Terrain(int gridX, int gridZ, Texture* texture)
		: worldPosX(gridX * SIZE), worldPosZ(gridZ * SIZE), texture(texture) {
			this->mesh = generateTerrain();
		}
		virtual ~Terrain() { delete mesh; }

		inline float getWorldPosX() const { return worldPosX; }
		inline float getWorldPosZ() const { return worldPosZ; }
		inline float getVertexCount() const { return VERTEX_COUNT; }

		inline Mesh* getMesh() { return mesh; }
		inline Texture* getTexture() { return texture; }
		
		inline glm::mat4 getModelMatrix() const { return modelMatrix; }
};