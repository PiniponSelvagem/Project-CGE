#pragma once
#include "../../../libs.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
	private:
		Material* material;
		Texture* overrideTextureDiffuse, *overrideTextureSpecular;
		Mesh* mesh;
		glm::vec3 position;


	public:
		Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, Mesh* mesh);
		Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, const char* objFile);
		~Model();

		inline void changeRotation(const glm::vec3 rotation) { mesh->changeRotation(rotation); }
		inline void changePosition(const glm::vec3 position) { mesh->changePosition(position); }
		
		void render(Shader* shader);
};