#pragma once
#include "Loader.h"

Mesh* Loader::load(std::vector<Vertex> vertex) {
	GLuint VAO;
	std::vector<GLuint> buffers;
	GLuint temp;
	// - VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// - VBO
	glGenBuffers(1, &temp);
	glBindBuffer(GL_ARRAY_BUFFER, temp);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	buffers.push_back(temp);

	// SET VERTEXATTRIBPOINTERS AND ENABLE
	// -- position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	// -- texcoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	// -- normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));


	// BIND VAO
	glBindVertexArray(0);

	return new Mesh(VAO, buffers, vertex.size(), 0);
}

Mesh* Loader::load_wIndices(std::vector<glm::vec3> vertices, std::vector<GLuint> indices, std::vector<VertexData> vertexData) {
	GLuint VAO;
	std::vector<GLuint> buffers;
	GLuint temp;
	// - VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// - EBO
	glGenBuffers(1, &temp);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	buffers.push_back(temp);


	// - VBO
	glGenBuffers(1, &temp);
	glBindBuffer(GL_ARRAY_BUFFER, temp);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	buffers.push_back(temp);

	// -- position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



	// - VBO
	glGenBuffers(1, &temp);
	glBindBuffer(GL_ARRAY_BUFFER, temp);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(VertexData), &vertexData[0], GL_STATIC_DRAW);
	buffers.push_back(temp);

	// -- texcoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, texcoord));
	// -- normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, normal));


	// BIND VAO
	glBindVertexArray(0);

	return new Mesh(VAO, buffers, vertices.size(), indices.size());
}