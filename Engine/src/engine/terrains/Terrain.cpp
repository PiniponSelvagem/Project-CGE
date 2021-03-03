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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<GLuint> indices;

	std::vector<VertexData> vertexData;

	std::vector<float> heightsRow;
	int vertexPointer = 0;
	for (float i = 0; i < vertexCount; i++) {
		for (float j = 0; j < vertexCount; j++) {
			float height = getHeightOfHMap((unsigned int)j, (unsigned int)i, hMap, width, channels);
			heightsRow.push_back(height);
			vertices.push_back(
				glm::vec3(
					j / (vertexCount - 1) * SIZE,
					height,
					i / (vertexCount - 1) * SIZE
				)
			);
			normals.push_back(calcNormal((unsigned int)j, (unsigned int)i, hMap, width, channels));
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
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++) {
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++) {
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

float Terrain::getHeightOfHMap(unsigned int x, unsigned int z, unsigned char *hMap, unsigned int imgWidth, unsigned int channels) {
	if (x >= imgWidth || z >= imgWidth) {
		return 0;
	}
	
	unsigned bytePerPixel = channels;
	unsigned int pixel = (x + imgWidth * z) * bytePerPixel;
	unsigned char* pixelOffset = hMap + pixel;
	unsigned char r = pixelOffset[0];
	unsigned char g = pixelOffset[1];
	unsigned char b = pixelOffset[2];
	//unsigned char a = channels >= 4 ? pixelOffset[3] : 0xff;

	float height = (float)((r << 8 * 2) | (g << 8) | b);
	height *= MAX_HEIGHT;
	height /= MAX_PIXEL_COLOR;
	return height;
}

glm::vec3 Terrain::calcNormal(unsigned int x, unsigned int z, unsigned char *hMap, unsigned int imgWidth, unsigned int channels) {
	float heightL = getHeightOfHMap(x - 1, z, hMap, imgWidth, channels);
	float heightR = getHeightOfHMap(x + 1, z, hMap, imgWidth, channels);
	float heightD = getHeightOfHMap(x, z - 1, hMap, imgWidth, channels);
	float heightU = getHeightOfHMap(x, z + 1, hMap, imgWidth, channels);
	glm::vec3 normal = glm::vec3(heightL-heightR, 2.f, heightD-heightU);
	normal = glm::normalize(normal);
	return normal;
}

float Terrain::getVertexHeight(float x, float z) {
	return heights[(int)z][(int)x];
}



Terrain::Terrain(int gridX, int gridZ,
		const char* heightMap, float size, float maxHeight,
		TerrainTexturePack* texturePack, Texture* blendMap
) : worldPosX(gridX* size), worldPosZ(gridZ* size), SIZE(size), MAX_HEIGHT(maxHeight),
	texturePack(texturePack), blendMap(blendMap)
{
	this->mesh = generateTerrain(heightMap);
}
Terrain::~Terrain() {
	delete blendMap;
	delete mesh;
}

float Terrain::getWorldPosX() {
	return worldPosX;
}
float Terrain::getWorldPosZ() {
	return worldPosZ;
}
unsigned int Terrain::getVertexCount() {
	return vertexCount;
}

float Terrain::getHeight(float worldX, float worldZ) {
	float terrainX = worldX - worldPosX;
	float terrainZ = worldZ - worldPosZ;
	float gridSquareSize = SIZE / (heights.size()-1);
	float gridX = glm::floor(terrainX / gridSquareSize);
	float gridZ = glm::floor(terrainZ / gridSquareSize);

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

Mesh* Terrain::getMesh() {
	return mesh;
}
TerrainTexturePack* Terrain::getTexturePack() {
	return texturePack;
}
Texture* Terrain::getBlendMap() {
	return blendMap;
}

glm::mat4 Terrain::getModelMatrix() {
	return modelMatrix;
}