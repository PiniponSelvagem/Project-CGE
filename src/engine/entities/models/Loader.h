#pragma once
#include "../../../libs.h"
#include "Mesh.h"

class Loader {
	public:
		static Mesh* load(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices);
};
