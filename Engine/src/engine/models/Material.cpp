#pragma once
#include <engine/models/Material.h>


Material::Material(glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex) {
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}
Material::~Material() { }

glm::vec3 Material::getSpecular() { return specular; }
glm::vec3 Material::getDiffuse()  { return diffuse;  }

GLint Material::getDiffuseTex()  { return diffuseTex;  }
GLint Material::getSpecularTex() { return specularTex; }