#pragma once
#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::~Material() { }

void Material::sendToShader(Shader &program) {
	program.setVec3f(ambient,  "material.ambient");
	program.setVec3f(diffuse,  "material.diffuse");
	program.setVec3f(specular, "material.specular");
	program.set1i(diffuseTex,  "material.diffuseTex");
	program.set1i(specularTex, "material.specularTex");
}