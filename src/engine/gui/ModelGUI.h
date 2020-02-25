#pragma once
#include "../../libs.h"
#include "../models/Vertex.h"
#include "../models/Mesh.h"
#include "../models/Texture.h"
#include "MaterialGUI.h"

class ModelGUI {
	private:
		MaterialGUI* material;
		Texture* overrideTextureDiffuse, *overrideTextureMask;
		std::vector<Mesh*> meshes;
		glm::vec3 position;


	public:
		ModelGUI(glm::vec3 position, MaterialGUI* material, Texture* ovTexDif, Texture* ovTexMask, std::vector<Mesh*> meshes);
		~ModelGUI();

		void changeRotation(const glm::vec3 rotation);
		void changePosition(const glm::vec3 position);


		void render(Shader* shader);
};