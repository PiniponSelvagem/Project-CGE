#pragma once
#include "../../libs.h"
#include "../models/Vertex.h"
#include "../models/Mesh.h"
#include "../models/Texture.h"
#include "MaterialUI.h"

class ModelUI {
	private:
		MaterialUI* material;
		Texture* overrideTextureDiffuse, *overrideTextureMask;
		std::vector<Mesh*> meshes;
		glm::vec3 position;


	public:
		ModelUI(glm::vec3 position, MaterialUI* material, Texture* ovTexDif, Texture* ovTexMask, std::vector<Mesh*> meshes);
		~ModelUI();

		void changeRotation(const glm::vec3 rotation);
		void changePosition(const glm::vec3 position);


		void render(Shader* shader);
};