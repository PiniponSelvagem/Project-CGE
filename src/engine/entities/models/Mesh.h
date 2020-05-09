#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"
#include "Vertex.h"

class Mesh {
	private:
		GLuint vao;
		std::vector<GLuint> buffers;
		GLuint nIndices;

	public:
		Mesh(GLuint vao, std::vector<GLuint> &buffers,  unsigned int nIndices)
			: vao(vao), buffers(buffers), nIndices(nIndices)
		{ }
		virtual ~Mesh() {
			glDeleteVertexArrays(1, &vao);
			for (size_t i = 0; i < buffers.size(); ++i) {
				glDeleteBuffers(1, &buffers[i]);
			}
		}

		inline GLuint getVaoID() { return vao; }
		inline unsigned getIndicesCount() { return nIndices; }
};