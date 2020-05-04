#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"
#include "Vertex.h"

class Mesh {
	private:
		Vertex* vertexArray;
		unsigned nVertices;
		GLuint* indexArray;
		unsigned nIndices;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		void Mesh_AuxCtor(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices);
		
		void initVAO();
		

	public:
		Mesh(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices);

		Mesh(const Mesh* mesh);
		~Mesh();

		inline GLuint getVaoID() { return VAO; }
		inline unsigned getVertexCount() { return nVertices; }
};