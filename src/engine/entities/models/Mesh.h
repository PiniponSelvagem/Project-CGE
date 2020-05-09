#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"
#include "Vertex.h"

class Mesh {
	private:
		GLuint vao, vbo;
		unsigned int nVertices;

	public:
		Mesh(GLuint vao, GLuint vbo,  unsigned int nVertices)
			: vao(vao), vbo(vbo), nVertices(nVertices)
		{ }
		virtual ~Mesh() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
		}

		inline GLuint getVaoID() { return vao; }
		inline unsigned getVerticesCount() { return nVertices; }
};