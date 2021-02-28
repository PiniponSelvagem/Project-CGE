#pragma once
#include <engine/Libs.h>

class Material {
	private:
		glm::vec3 specular;
		glm::vec3 diffuse;
		GLint diffuseTex;
		GLint specularTex;


	public:
		Material(glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
		virtual ~Material();

		glm::vec3 getSpecular();
		glm::vec3 getDiffuse();

		GLint getDiffuseTex();
		GLint getSpecularTex();
};