#pragma once
#include "Primitive.h"

Triangle::Triangle() : Primitive() {
	Vertex vertices[] = {
		//Position							//Color							//Texcoords					//Normals				
		glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f,-0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f,-0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)
	};
	unsigned nVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] = {
		0, 1, 2
	};
	unsigned nIndices = sizeof(indices) / sizeof(GLuint);

	set(vertices, nVertices, indices, nIndices);
}