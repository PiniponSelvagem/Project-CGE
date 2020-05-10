#pragma once
#include "../../../libs.h"

class Material {
	private:
		glm::vec3 ambient;
		glm::vec3 specular;
		glm::vec3 diffuse;
		GLint diffuseTex;
		GLint specularTex;


	public:
		Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
			: ambient(ambient), diffuse(diffuse), specular(specular), diffuseTex(diffuseTex), specularTex(specularTex)
		{ }
		virtual ~Material() { }

		inline glm::vec3 getAmbient() const  { return ambient; }
		inline glm::vec3 getSpecular() const { return specular; }
		inline glm::vec3 getDiffuse() const  { return diffuse; }

		inline GLint getDiffuseTex() const  { return diffuseTex; }
		inline GLint getSpecularTex() const { return specularTex; }
};