#pragma once
#include <engine/Libs.h>
#include <engine/shaders/Shader.h>
#include <engine/models/Vertex.h>

class Mesh {
	private:
		GLuint vao;
		std::vector<GLuint> buffers;
		unsigned int nVertices, nIndices;

	public:
		Mesh(GLuint vao, std::vector<GLuint>& buffers, unsigned int nVertices, unsigned int nIndices);
		virtual ~Mesh();

		GLuint getVaoID();

		unsigned getVerticesCount();
		unsigned getIndicesCount();
};