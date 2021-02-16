#pragma once
#include "../../libs.h"
#include "Mesh.h"

class Loader {
	public:
		static Mesh* load(
			std::vector<Vertex> vertexData
		);

		static Mesh* load_wIndices(
			std::vector<glm::vec3> positions,
			std::vector<GLuint> indices,
			std::vector<VertexData> vertexData
		);

		// Used to load UI quad
		static Mesh* load_simple2D(
			std::vector<glm::vec2> positions
		);
};
