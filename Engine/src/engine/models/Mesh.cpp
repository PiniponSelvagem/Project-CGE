#pragma once
#include <engine/models/Mesh.h>


Mesh::Mesh(GLuint vao, std::vector<GLuint>& buffers, unsigned int nVertices, unsigned int nIndices) {
	this->vao = vao;
	this->buffers = buffers;
	this->nVertices = nVertices;
	this->nIndices = nIndices;
}
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	for (size_t i = 0; i < buffers.size(); ++i) {
		glDeleteBuffers(1, &buffers[i]);
	}
}

GLuint Mesh::getVaoID() { return vao; }

unsigned Mesh::getVerticesCount() { return nVertices; }
unsigned Mesh::getIndicesCount()  { return nIndices;  }