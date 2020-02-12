#pragma once

class Model {
	private:
		Material *material;
		Texture *overrideTextureDiffuse, *overrideTextureSpecular;
		std::vector<Mesh*> meshes;
		glm::vec3 position;


		void updateUniforms() {

		}


	public:
		Model(glm::vec3 position, Material *material, Texture *ovTexDif, Texture *ovTexSpec, std::vector<Mesh*> meshes) {
			this->position = position;
			this->material = material;
			this->overrideTextureDiffuse = ovTexDif;
			this->overrideTextureSpecular = ovTexSpec;

			// Range-for --- C++11
			for (auto *i : meshes) {
				this->meshes.push_back(new Mesh(*i));
			}
		}

		~Model() {
			for (auto *&i : meshes) {
				delete i;
			}
		}

		void changeRotation(const glm::vec3 rotation) {
			for (auto &i : meshes) {
				i->changeRotation(rotation);
			}
		}

		void update() {
			updateUniforms();
		}

		void render(Shader *shader) {
			updateUniforms();
			material->sendToShader(*shader);

			shader->use();

			overrideTextureDiffuse->bind(0);
			overrideTextureSpecular->bind(1);

			for (auto &i : meshes) {
				i->render(shader);
			}

			glBindVertexArray(0);
			glUseProgram(0);
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
};