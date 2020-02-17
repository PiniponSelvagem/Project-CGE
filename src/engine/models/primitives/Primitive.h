#pragma once
#include "../../../libs.h"
#include "../Vertex.h"

class Primitive {
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;


	public:
		Primitive();
		virtual ~Primitive();

		void set(const Vertex * vertices, const unsigned nVertices, const GLuint * indices, const unsigned nIndices);

		inline Vertex * getVertices() {
			return vertices.data();
		}
		inline GLuint * getIndices() {
			return indices.data();
		}

		inline const unsigned getNrVertices() {
			return vertices.size();
		}
		inline const unsigned getNrIndices() {
			return indices.size();
		}
};


class Triangle : public Primitive {
	public:
		Triangle();
};
class Quad : public Primitive {
	public:
		Quad();
};
class Cube : public Primitive {
	public:
		Cube();
};