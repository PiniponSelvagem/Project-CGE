#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"
#include "Vertex.h"

class Mesh {
	private:
		GLuint vao;
		std::vector<GLuint> buffers;
		unsigned int nVertices, nIndices;

	public:
		Mesh(GLuint vao, std::vector<GLuint> &buffers, unsigned int nVertices, unsigned int nIndices)
			: vao(vao), buffers(buffers), nVertices(nVertices), nIndices(nIndices)
		{ }
		virtual ~Mesh() {
			glDeleteVertexArrays(1, &vao);
			for (size_t i = 0; i < buffers.size(); ++i) {
				glDeleteBuffers(1, &buffers[i]);
			}
		}

		inline GLuint getVaoID() const { return vao; }
		inline unsigned getVerticesCount() const { return nVertices; }
		inline unsigned getIndicesCount() const  { return nIndices; }
};