#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"

class Material {
	private:
		glm::vec3 ambient;
		glm::vec3 specular;
		glm::vec3 diffuse;
		GLint diffuseTex;
		GLint specularTex;



	public:
		Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
		~Material();

		void sendToShader(Shader &program);
};