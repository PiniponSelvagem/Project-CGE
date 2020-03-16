#pragma once
#include "../../libs.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
	private:
		Material* material;
		Texture* overrideTextureDiffuse, *overrideTextureSpecular;
		std::vector<Mesh*> meshes;
		glm::vec3 position;


	public:
		Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, std::vector<Mesh*> meshes);
		Model(glm::vec3 position, Material* material, Texture* ovTexDif, Texture* ovTexSpec, const char* objFile);
		~Model();

		void changeRotation(const glm::vec3 rotation);
		void changePosition(const glm::vec3 position);
		
		void render(Shader* shader);
};