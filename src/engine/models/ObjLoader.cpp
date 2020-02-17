#pragma once
#include "ObjLoader.h"

std::vector<Vertex> ObjLoader::loadObj(const char* fileName) {
	// Vertex portions
	std::vector<glm::fvec3> vertexPositions;
	std::vector<glm::fvec2> vertexTexCoords;
	std::vector<glm::fvec3> vertexNormals;

	// Face vectors
	std::vector<GLint> vertexPositionIndices;
	std::vector<GLint> vertexTexCoordIndices;
	std::vector<GLint> vertexNormalIndices;

	// Vertex array
	std::vector<Vertex> vertices;

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
		ss >> prefix;
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
				if (p == 0) { vertexPositionIndices.push_back(tempGLint); }
				else if (p == 1) { vertexTexCoordIndices.push_back(tempGLint); }
				else if (p == 2) { vertexNormalIndices.push_back(tempGLint); }

				if (ss.peek() == '/') { ++p; ss.ignore(1, '/'); }
				else if (ss.peek() == ' ') { ++p; ss.ignore(1, ' '); }

				if (p > 2) p = 0;
			}
		}

		vertices.resize(vertexPositionIndices.size(), Vertex());

		for (size_t i = 0; i < vertexPositionIndices.size(); ++i) {
			vertices[i].position = vertexPositions[vertexPositionIndices[i] - 1];
			vertices[i].texcoord = vertexTexCoords[vertexTexCoordIndices[i] - 1];
			vertices[i].normal = vertexNormals[vertexNormalIndices[i] - 1];
			vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
		}

		//std::cout << "Nr of vertices: " << vertices.size() << std::endl;
	}

	return vertices;
}