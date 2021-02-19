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
		Mesh(GLuint vao, std::vector<GLuint> &buffers, unsigned int nVertices, unsigned int nIndices)
			: vao(vao), buffers(buffers), nVertices(nVertices), nIndices(nIndices)
		{ }
		virtual ~Mesh() {
			glDeleteVertexArrays(1, &vao);
			for (size_t i = 0; i < buffers.size(); ++i) {
				glDeleteBuffers(1, &buffers[i]);
			}
		}

		inline GLuint getVaoID() { return vao; }
		inline unsigned getVerticesCount() { return nVertices; }
		inline unsigned getIndicesCount() { return nIndices; }
};