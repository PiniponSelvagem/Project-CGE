#pragma once
#include "Terrain.h"

#include "../models/Loader.h"

Mesh* Terrain::generateTerrain() {
	float count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<GLuint> indices;

	std::vector<VertexData> vertexData;

	int vertexPointer = 0;
	for (float i = 0; i < VERTEX_COUNT; i++) {
		for (float j = 0; j < VERTEX_COUNT; j++) {
			vertices.push_back(
				glm::vec3(
					j / (VERTEX_COUNT - 1) * SIZE, 
					0,
					i / (VERTEX_COUNT - 1) * SIZE
				)
			);
			normals.push_back(glm::vec3(0.f, 1.f, 0.f));
			texcoords.push_back(
				glm::vec2(
					j / (VERTEX_COUNT - 1),
					i / (VERTEX_COUNT - 1)
				)
			);
			vertexData.push_back(VertexData());
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}

	for (int i = 0; i < normals.size(); ++i) {
		vertexData[i].normal = normals[i];
		vertexData[i].texcoord = texcoords[i];
	}

	modelMatrix = glm::translate(modelMatrix, glm::vec3(worldPosX, 0, worldPosZ));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));

	return Loader::load_wIndices(vertices, indices, vertexData);
}