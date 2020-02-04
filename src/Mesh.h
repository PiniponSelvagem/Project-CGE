
class Mesh {
	private:
		std::vector<Vertex> vertices;	//Should use pointers instead, or this will waste memory
		std::vector<GLuint> indices;	//Should use pointers instead, or this will waste memory

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 ModelMatrix;

		void initVertexData(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices) {
			for (size_t i = 0; i < nVertices; ++i) {
				this->vertices.push_back(vertexArray[i]);
			}

			for (size_t i = 0; i < nIndices; ++i) {
				this->indices.push_back(indexArray[i]);
			}
		}

		void initVAO() {
			// - VAO
			glGenVertexArrays(1, &this->VAO);
			glBindVertexArray(this->VAO);

			// - VBO
			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

			// - EBO
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

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

		void initModelMatrix() {
			this->position = glm::vec3(0.f);
			this->rotation = glm::vec3(0.f);
			this->scale = glm::vec3(1.f);

			this->ModelMatrix = glm::mat4(1.f);
			this->ModelMatrix = glm::translate(ModelMatrix, this->position);
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
			this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
			this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
		}

		void updateUniforms(Shader * shader) {
			shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
		}

		

	public:
		Mesh(Vertex * vertexArray, const unsigned &nVertices, GLuint * indexArray, const unsigned &nIndices) {
			this->initVertexData(vertexArray, nVertices, indexArray, nIndices);
			this->initVAO();
			this->initModelMatrix();
		}

		~Mesh() {
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
			glDeleteBuffers(1, &this->EBO);
		}

		void update(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale) {
			this->ModelMatrix = glm::mat4(1.f);
			this->ModelMatrix = glm::translate(ModelMatrix, position);
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
			this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
			this->ModelMatrix = glm::scale(ModelMatrix, scale);
		}

		void render(Shader * shader) {
			this->updateUniforms(shader);
			shader->use();

			glBindVertexArray(VAO);
			//if (this->indices.empty())
			//	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
			//else
				glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		}
};