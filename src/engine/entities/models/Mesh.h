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

		glm::vec3 position;
		glm::vec3 origin;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 ModelMatrix;

		void Mesh_AuxCtor(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices,
						  glm::vec3 position = glm::vec3(0.f),
						  glm::vec3 origin = glm::vec3(0.f),
						  glm::vec3 rotation = glm::vec3(0.f),
						  glm::vec3 scale = glm::vec3(1.f)
		);
		
		void initVAO();
		
		void updateUniforms(Shader* shader);

		void updateModelMatrix();

		

	public:
		Mesh(Vertex* vertexArray, const unsigned &nVertices, GLuint* indexArray, const unsigned &nIndices,
			 glm::vec3 position = glm::vec3(0.f),
			 glm::vec3 origin = glm::vec3(0.f),
			 glm::vec3 rotation = glm::vec3(0.f),
			 glm::vec3 scale = glm::vec3(1.f)
		);

		Mesh(const Mesh &mesh);
		~Mesh();

		inline void setOrigin(const glm::vec3 origin) { this->origin = origin; }
		inline void setPosition(const glm::vec3 position) { this->position = position; }
		inline void setRotation(const glm::vec3 rotation) { this->rotation = rotation; }
		inline void setScale(const glm::vec3 scale) { this->scale = scale; }

		inline void changePosition(const glm::vec3 position) {
			this->position += position;
			this->origin += position;
		}
		inline void changePosition_keepOrigin(const glm::vec3 position) { this->position += position; } // Useful to create orbiting objects
		inline void changeRotation(const glm::vec3 rotation) {
			this->rotation += rotation;
			if (this->rotation.x > 360)
				this->rotation.x = 0;
			else if (this->rotation.x = -1)
				this->rotation.x = 359;
		}
		inline void changeScale(const glm::vec3 scale) { this->scale += scale; }

		void render(Shader* shader);
};