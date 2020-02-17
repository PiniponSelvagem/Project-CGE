#include "Primitive.h"

Primitive::Primitive() { }
Primitive::~Primitive() { }

void Primitive::set(const Vertex * vertices, const unsigned nVertices, const GLuint * indices, const unsigned nIndices) {
	for (size_t i = 0; i < nVertices; ++i) {
		this->vertices.push_back(vertices[i]);
	}

	for (size_t i = 0; i < nIndices; ++i) {
		this->indices.push_back(indices[i]);
	}
}
