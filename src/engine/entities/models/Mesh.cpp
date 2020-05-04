#pragma once
#include "Mesh.h"

void Mesh::Mesh_AuxCtor(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices) {
	this->nVertices = nVertices;
	this->nIndices = nIndices;

	this->vertexArray = new Vertex[this->nVertices];
	for (size_t i = 0; i < nVertices; ++i) {
		this->vertexArray[i] = vertexArray[i];
	}

	this->indexArray = new GLuint[this->nIndices];
	for (size_t i = 0; i < nIndices; ++i) {
		this->indexArray[i] = indexArray[i];
	}

	initVAO();
}

void Mesh::initVAO() {
	// - VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// - VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

	// - EBO
	if (this->nIndices > 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}

	// SET VERTEXATTRIBPOINTERS AND ENABLE
	// -- position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// -- color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// -- texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	// -- normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// BIND VAO
	glBindVertexArray(0);
}


Mesh::Mesh(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices) {
	Mesh_AuxCtor(vertexArray, nVertices, indexArray, nIndices);
}


Mesh::Mesh(const Mesh* mesh) {
	Mesh_AuxCtor(mesh->vertexArray, mesh->nVertices, mesh->indexArray, mesh->nIndices);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (nIndices > 0) {
		glDeleteBuffers(1, &EBO);
	}

	delete[] vertexArray;
	delete[] indexArray;
}
