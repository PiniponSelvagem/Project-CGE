#pragma once

class Primitive {
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;


	public:
		Primitive() {}
		virtual ~Primitive() {}

		void set(const Vertex * vertices, const unsigned nVertices, const GLuint * indices, const unsigned nIndices) {
			for (size_t i = 0; i < nVertices; ++i) {
				this->vertices.push_back(vertices[i]);
			}

			for (size_t i = 0; i < nIndices; ++i) {
				this->indices.push_back(indices[i]);
			}
		}

		inline Vertex * getVertices() {
			return this->vertices.data();
		}

		inline GLuint * getIndices() {
			return this->indices.data();
		}

		inline const unsigned getNrVertices() {
			return this->vertices.size();
		}

		inline const unsigned getNrIndices() {
			return this->indices.size();
		}
};



class Quad : public Primitive {
	public:
		Quad() : Primitive() {
			Vertex vertices[] = {
				//Position							//Color							//Texcoords					//Normals				
				glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(-0.5f,-0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.5f,-0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
			};
			unsigned nVertices = sizeof(vertices) / sizeof(Vertex);

			GLuint indices[] = {
				0, 1, 2,	//Tri 1
				0, 2, 3,	//Tri 2
			};
			unsigned nIndices = sizeof(indices) / sizeof(GLuint);

			this->set(vertices, nVertices, indices, nIndices);
		}
};

class Triangle : public Primitive {
	public:
	Triangle() : Primitive() {
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

		this->set(vertices, nVertices, indices, nIndices);
	}
};