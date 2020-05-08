#pragma once
#include "Loader.h"

Mesh* Loader::load(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices) {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO = 0;

	// - VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// - VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

	// - EBO
	if (nIndices > 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
	}

	// SET VERTEXATTRIBPOINTERS AND ENABLE
	// -- position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// -- texcoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(1);
	// -- normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	// -- color
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(3);

	// BIND VAO
	glBindVertexArray(0);

	return new Mesh(VAO, VBO, EBO, nVertices);
}
