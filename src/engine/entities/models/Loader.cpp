#pragma once
#include "Loader.h"

Mesh* Loader::load(std::vector<glm::vec3> vertices, std::vector<GLuint> indices, std::vector<Vertex> vertexData) {
	GLuint VAO, VBO;
	GLuint temp;
	// - VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	// - EBO
	//if (indices.size() > 0) {
	//	glGenBuffers(1, &temp);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	//	buffers.push_back(temp);
	//}

	// - VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), &vertexData[0], GL_STATIC_DRAW);

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

	//return new Mesh(VAO, buffers, indices.size());
	return new Mesh(VAO, VBO, vertexData.size());
}