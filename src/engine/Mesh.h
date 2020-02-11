#pragma once

class Mesh {
	private:
		unsigned nVertices;
		unsigned nIndices;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 ModelMatrix;

		

		void initVAO(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices) {
			this->nVertices = nVertices;
			this->nIndices = nIndices;

			// - VAO
			glGenVertexArrays(1, &this->VAO);
			glBindVertexArray(this->VAO);

			// - VBO
			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->nVertices*sizeof(Vertex), vertexArray, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

			// - EBO
			if (this->nIndices > 0) {
				glGenBuffers(1, &this->EBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
			}

			// SET VERTEXATTRIBPOINTERS AND ENABLE
			// -- position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);
			// -- color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
			glEnableVertexAttribArray(1);
			// -- texcoord
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
			glEnableVertexAttribArray(2);
			// -- normal
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(3);

			// BIND VAO
			glBindVertexArray(0);
		}
		void initVAO(Primitive * primitive) {
			this->nVertices = primitive->getNrVertices();
			this->nIndices = primitive->getNrIndices();;

			// - VAO
			glGenVertexArrays(1, &this->VAO);
			glBindVertexArray(this->VAO);

			// - VBO
			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->nVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

			// - EBO
			if (this->nIndices > 0) {
				glGenBuffers(1, &this->EBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);
			}
			
			// SET VERTEXATTRIBPOINTERS AND ENABLE
			// -- position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);
			// -- color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
			glEnableVertexAttribArray(1);
			// -- texcoord
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
			glEnableVertexAttribArray(2);
			// -- normal
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(3);

			// BIND VAO
			glBindVertexArray(0);
		}
		
		void updateUniforms(Shader * shader) {
			shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
		}

		void updateModelMatrix() {
			this->ModelMatrix = glm::mat4(1.f);
			this->ModelMatrix = glm::translate(ModelMatrix, this->position);
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
			this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
		}

		

	public:
		Mesh(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices,
				glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f)
			) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;

			this->initVAO(vertexArray, nVertices, indexArray, nIndices);
			this->updateModelMatrix();
		}

		Mesh(Primitive * primitive,
			glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f)
		) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;

			this->initVAO(primitive);
			this->updateModelMatrix();
		}

		~Mesh() {
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
			if (this->nIndices > 0) {
				glDeleteBuffers(1, &this->EBO);
			}
		}

		void setPosition(const glm::vec3 position) {
			this->position = position;
		}
		void setRotation(const glm::vec3 rotation) {
			this->rotation = rotation;
		}
		void setScale(const glm::vec3 scale) {
			this->scale = scale;
		}

		void changePosition(const glm::vec3 position) {
			this->position += position;
		}
		void changeRotation(const glm::vec3 rotation) {
			this->rotation += rotation;
			if (this->rotation.x > 360)
				this->rotation.x = 0;
			else if (this->rotation.x = -1)
				this->rotation.x = 359;
		}
		void changeScale(const glm::vec3 scale) {
			this->scale += scale;
		}

		void update() {
			/*
			this->ModelMatrix = glm::mat4(1.f);
			this->ModelMatrix = glm::translate(ModelMatrix, position);
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
			this->ModelMatrix = glm::scale(ModelMatrix, scale);
			*/
		}

		void render(Shader * shader) {
			this->updateModelMatrix();
			this->updateUniforms(shader);
			shader->use();

			glBindVertexArray(this->VAO);
			if (this->nIndices == 0)
				glDrawArrays(GL_TRIANGLES, 0, this->nVertices);
			else
				glDrawElements(GL_TRIANGLES, this->nIndices, GL_UNSIGNED_INT, 0);
		}
};