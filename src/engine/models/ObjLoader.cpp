#pragma once
#include "ObjLoader.h"
#include "Loader.h"

Mesh* ObjLoader::loadObj(const char* fileName) {
	// Vertex portions
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;

	// Face vectors
	std::vector<GLuint> indices;

	std::vector<VertexData> vertexData;

	std::ifstream inFile(fileName);

	if (!inFile.is_open()) {
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;
	GLint tempGLint = 0;

	while (std::getline(inFile, line)) {
		ss.clear();
		ss.str(line);
		if (line.size() > 1) ss >> prefix;
		else prefix = "";

		if (prefix == "v") {
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertices.push_back(tempVec3);
		}
		else if (prefix == "vt") {
			ss >> tempVec2.x >> tempVec2.y;
			texcoords.push_back(tempVec2);
		}
		else if (prefix == "vn") {
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			normals.push_back(tempVec3);
		}
		else if (prefix == "f") {
			vertexData.resize(vertices.size(), VertexData());
			break;
		}
	}

	do {
		ss.clear();
		ss.str(line);
		if (line.size() > 1) ss >> prefix;
		else prefix = "";

		if (prefix == "f") {
			int verticeIndex = 0;
			int p = 0;
			while (ss >> tempGLint) {
				if (p == 0) {
					verticeIndex = tempGLint - 1;
					indices.push_back(verticeIndex);
				}
				else if (p == 1) {
					vertexData[verticeIndex].texcoord = texcoords[tempGLint - 1];
				}
				else if (p == 2) {
					vertexData[verticeIndex].normal = normals[tempGLint - 1];
				}

				if (ss.peek() == '/') { ++p; ss.ignore(1, '/'); }
				else if (ss.peek() == ' ') { ++p; ss.ignore(1, ' '); }

				if (p > 2) p = 0;
			}
		}
	} while (std::getline(inFile, line));

	//std::cout << "Nr of vertices: " << verticesData.size() << std::endl;
	
	return Loader::load_wIndices(
		vertices,
		indices,
		vertexData
	);
}

Mesh* ObjLoader::loadObj_arrays(const char* fileName) {
	// Vertex portions
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexTexCoords;
	std::vector<glm::vec3> vertexNormals;

	// Face vectors
	std::vector<GLuint> vertexPositionIndices;
	std::vector<GLuint> vertexTexCoordIndices;
	std::vector<GLuint> vertexNormalIndices;

	// Vertex array
	std::vector<Vertex> verticesData;

	std::ifstream inFile(fileName);

	if (!inFile.is_open()) {
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;
	GLint tempGLint = 0;

	while (std::getline(inFile, line)) {
		ss.clear();
		ss.str(line);
		if (line.size() > 1) ss >> prefix;
		else prefix = "";

		if (prefix == "o") { }
		else if (prefix == "s") { }
		else if (prefix == "v") { // Vertex position
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt") {
			ss >> tempVec2.x >> tempVec2.y;
			vertexTexCoords.push_back(tempVec2);
		}
		else if (prefix == "vn") {
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f") {
			int p = 0;
			while (ss >> tempGLint) {
				if (p == 0) { vertexPositionIndices.push_back(tempGLint-1); }
				else if (p == 1) { vertexTexCoordIndices.push_back(tempGLint-1); }
				else if (p == 2) { vertexNormalIndices.push_back(tempGLint-1); }

				if (ss.peek() == '/') { ++p; ss.ignore(1, '/'); }
				else if (ss.peek() == ' ') { ++p; ss.ignore(1, ' '); }

				if (p > 2) p = 0;
			}
		}
	}

	verticesData.resize(vertexPositionIndices.size(), Vertex());

	for (size_t i = 0; i < vertexPositionIndices.size(); ++i) {
		verticesData[i].position = vertexPositions[vertexPositionIndices[i]];

		verticesData[i].texcoord.x = vertexTexCoords[vertexTexCoordIndices[i]].x;
		verticesData[i].texcoord.y = vertexTexCoords[vertexTexCoordIndices[i]].y * -1.f;	// Flip vertically for OpenGL

		verticesData[i].normal = vertexNormals[vertexNormalIndices[i]];
	}

	//std::cout << "Nr of vertices: " << verticesData.size() << std::endl;
	
	return Loader::load(
		verticesData
	);
}
