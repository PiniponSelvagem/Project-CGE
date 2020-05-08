#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"
#include "Vertex.h"

class Mesh {
	private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		unsigned int nIndices;

	public:
		Mesh(GLuint vao, GLuint vbo, GLuint ebo, unsigned int nIndices)
			: vao(vao), vbo(vbo), ebo(ebo), nIndices(nIndices)
		{ }
		virtual ~Mesh() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			if (ebo != 0) {
				glDeleteBuffers(1, &ebo);
			}
		}

		inline GLuint getVaoID() { return vao; }
		inline unsigned getIndicesCount() { return nIndices; }
};