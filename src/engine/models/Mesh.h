#pragma once
#include "../../libs.h"
#include "../Shader.h"
#include "Vertex.h"
#include "primitives/Primitive.h"

class Mesh {
	private:
		Vertex *vertexArray;
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

		void Mesh_AuxCtor(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices,
						  glm::vec3 position = glm::vec3(0.f),
						  glm::vec3 origin = glm::vec3(0.f),
						  glm::vec3 rotation = glm::vec3(0.f),
						  glm::vec3 scale = glm::vec3(1.f)
		);
		
		void initVAO();
		
		void updateUniforms(Shader * shader);

		void updateModelMatrix();

		

	public:
		Mesh(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices,
			 glm::vec3 position = glm::vec3(0.f),
			 glm::vec3 origin = glm::vec3(0.f),
			 glm::vec3 rotation = glm::vec3(0.f),
			 glm::vec3 scale = glm::vec3(1.f)
		);

		Mesh(Primitive * primitive,
			 glm::vec3 position = glm::vec3(0.f),
			 glm::vec3 origin = glm::vec3(0.f),
			 glm::vec3 rotation = glm::vec3(0.f),
			 glm::vec3 scale = glm::vec3(1.f)
		);

		Mesh(const Mesh &mesh);

		~Mesh();

		void setOrigin(const glm::vec3 origin);
		void setPosition(const glm::vec3 position);
		void setRotation(const glm::vec3 rotation);
		void setScale(const glm::vec3 scale);

		void changePosition(const glm::vec3 position);
		void changePosition_keepOrigin(const glm::vec3 position); // Useful to create orbiting objects
		void changeRotation(const glm::vec3 rotation);
		void changeScale(const glm::vec3 scale);

		void update();

		void render(Shader * shader);
};