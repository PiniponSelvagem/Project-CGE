#pragma once

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
		) {
			this->position = position;
			this->origin = origin;
			this->rotation = rotation;
			this->scale = scale;

			this->nVertices = nVertices;
			this->nIndices = nIndices;

			this->vertexArray = new Vertex[this->nVertices];
			for (size_t i = 0; i < nVertices; ++i) {
				this->vertexArray[i] = vertexArray[i];
			}

			this->indexArray = new GLuint[this->nIndices];
			for (size_t i = 0; i < nIndices; ++i) {
				this->indexArray[i] = indexArray[i];
			}

			initVAO();
			updateModelMatrix();
		}
		
		void initVAO() {
			// - VAO
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			// - VBO
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

			// - EBO
			if (this->nIndices > 0) {
				glGenBuffers(1, &EBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
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
			shader->setMat4fv(ModelMatrix, "ModelMatrix");
		}

		void updateModelMatrix() {
			this->ModelMatrix = glm::mat4(1.f);
			this->ModelMatrix = glm::translate(ModelMatrix, origin);
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
			this->ModelMatrix = glm::translate(ModelMatrix, position - origin);
			this->ModelMatrix = glm::scale(ModelMatrix, scale);
		}

		

	public:
		Mesh(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices,
				glm::vec3 position = glm::vec3(0.f),
				glm::vec3 origin = glm::vec3(0.f),
				glm::vec3 rotation = glm::vec3(0.f),
				glm::vec3 scale = glm::vec3(1.f)
		) {
			Mesh_AuxCtor(
				vertexArray, nVertices, indexArray, nIndices,
				position, origin, rotation, scale
			);
		}

		Mesh(Primitive * primitive,
			glm::vec3 position = glm::vec3(0.f),
			glm::vec3 origin = glm::vec3(0.f),
			glm::vec3 rotation = glm::vec3(0.f),
			glm::vec3 scale = glm::vec3(1.f)
		) {
			Mesh_AuxCtor(
				primitive->getVertices(), primitive->getNrVertices(), primitive->getIndices(), primitive->getNrIndices(),
				position, origin, rotation, scale
			);
		}

		Mesh(const Mesh &mesh) {
			Mesh_AuxCtor(
				mesh.vertexArray, mesh.nVertices, mesh.indexArray, mesh.nIndices,
				mesh.position, mesh.origin, mesh.rotation, mesh.scale
			);
		}

		~Mesh() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			if (nIndices > 0) {
				glDeleteBuffers(1, &EBO);
			}

			delete[] vertexArray;
			delete[] indexArray;
		}

		void setOrigin(const glm::vec3 origin) {
			this->origin = origin;
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
			this->origin += position;
		}
		void changePosition_keepOrigin(const glm::vec3 position) { // Useful to create orbiting objects
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
			updateModelMatrix();
			updateUniforms(shader);
			shader->use();

			glBindVertexArray(VAO);
			if (nIndices == 0)
				glDrawArrays(GL_TRIANGLES, 0, nVertices);
			else
				glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
		}
};