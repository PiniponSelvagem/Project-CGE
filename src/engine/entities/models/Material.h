#pragma once
#include "../../../libs.h"

class Material {
	private:
		glm::vec3 specular;
		glm::vec3 diffuse;
		GLint diffuseTex;
		GLint specularTex;


	public:
		Material(glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
			: diffuse(diffuse), specular(specular), diffuseTex(diffuseTex), specularTex(specularTex)
		{ }
		virtual ~Material() { }

		inline glm::vec3 getSpecular() { return specular; }
		inline glm::vec3 getDiffuse()  { return diffuse; }

		inline GLint getDiffuseTex()  { return diffuseTex; }
		inline GLint getSpecularTex() { return specularTex; }
};