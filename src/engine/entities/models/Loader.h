#pragma once
#include "../../../libs.h"
#include "Mesh.h"

class Loader {
	//private:
	//	static GLuint storeDataInAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);

	public:
		static Mesh* load(
			std::vector<glm::vec3> vertices,
			std::vector<GLuint> indices,
			std::vector<Vertex> vertexData
		);
};
