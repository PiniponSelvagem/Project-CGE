#pragma once
#include <engine/terrains/Terrain.h>
#include <engine/utils/Utils.h>
#include <engine/models/Loader.h>


Mesh* Terrain::generateTerrain(const char* heightMap) {
	int width, height, channels;
    unsigned char *hMap = stbi_load(heightMap, &width, &height, &channels, 0);
    if (hMap == NULL) {
		std::cout << "ERROR::TERRAIN::generateTerrain: Could not load " << heightMap << std::endl;
	}
	else if (width != height) {
		std::cout << "WARN::TERRAIN::generateTerrain: " << heightMap << " height and width do not match. Unexcepted results might occur." << std::endl;
	}
	
	vertexCount = width;

	float count = vertexCount * vertexCount;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<GLuint> indices;

	std::vector<VertexData> vertexData;

	std::vector<float> heightsRow;
	int vertexPointer = 0;
	for (float i = 0; i < vertexCount; i++) {
		for (float j = 0; j < vertexCount; j++) {
			float height = getHeightOfHMap(j, i, hMap, width, channels);
			heightsRow.push_back(height);
			vertices.push_back(
				glm::vec3(
					j / (vertexCount - 1) * SIZE,
					height,
					i / (vertexCount - 1) * SIZE
				)
			);
			normals.push_back(calcNormal(j, i, hMap, width, channels));
			texcoords.push_back(
				glm::vec2(
					j / (vertexCount - 1),
					i / (vertexCount - 1)
				)
			);
			vertexData.push_back(VertexData());
			vertexPointer++;
		}
		heights.push_back(heightsRow);
		heightsRow.clear();
	}
	int pointer = 0;
	for (int gz = 0; gz < vertexCount - 1; gz++) {
		for (int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz*vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*vertexCount) + gx;
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

	delete hMap;
	return Loader::load_wIndices(vertices, indices, vertexData);
}

float Terrain::getHeightOfHMap(unsigned x, unsigned z, unsigned char *hMap, unsigned imgWidth, unsigned channels) {
	if (x >= imgWidth || z >= imgWidth) {
		return 0;
	}
	
	unsigned bytePerPixel = channels;
	unsigned char* pixelOffset = hMap + (x + imgWidth * z) * bytePerPixel;
	unsigned char r = pixelOffset[0];
	unsigned char g = pixelOffset[1];
	unsigned char b = pixelOffset[2];
	//unsigned char a = channels >= 4 ? pixelOffset[3] : 0xff;

	float height = (r << 8 * 2) | (g << 8) | b;
	height *= MAX_HEIGHT;
	height /= MAX_PIXEL_COLOR;
	return height;
}

glm::vec3 Terrain::calcNormal(unsigned x, unsigned z, unsigned char *hMap, unsigned imgWidth, unsigned channels) {
	float heightL = getHeightOfHMap(x - 1, z, hMap, imgWidth, channels);
	float heightR = getHeightOfHMap(x + 1, z, hMap, imgWidth, channels);
	float heightD = getHeightOfHMap(x, z - 1, hMap, imgWidth, channels);
	float heightU = getHeightOfHMap(x, z + 1, hMap, imgWidth, channels);
	glm::vec3 normal = glm::vec3(heightL-heightR, 2.f, heightD-heightU);
	normal = glm::normalize(normal);
	return normal;
}

float Terrain::getVertexHeight(float x, float z) {
	return heights[z][x];
}




float Terrain::getHeight(float worldX, float worldZ) {
	float terrainX = worldX - worldPosX;
	float terrainZ = worldZ - worldPosZ;
	float gridSquareSize = SIZE / (heights.size()-1);
	int gridX = glm::floor(terrainX / gridSquareSize);
	int gridZ = glm::floor(terrainZ / gridSquareSize);

	if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0)
		return 0;

	float xcoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zcoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	
	float res;
	if (xcoord <= (1 - zcoord)) {
		res = Utils::barryCentric(
			glm::vec3(0, getVertexHeight(gridX, gridZ), 0),
			glm::vec3(1, getVertexHeight(gridX + 1, gridZ), 0),
			glm::vec3(0, getVertexHeight(gridX, gridZ + 1), 1),
			glm::vec2(xcoord, zcoord)
		);
	}
	else {
		res = Utils::barryCentric(
			glm::vec3(1, getVertexHeight(gridX + 1, gridZ), 0),
			glm::vec3(1, getVertexHeight(gridX + 1, gridZ + 1), 1),
			glm::vec3(0, getVertexHeight(gridX, gridZ + 1), 1),
			glm::vec2(xcoord, zcoord)
		);
	}
	
	return res;
}