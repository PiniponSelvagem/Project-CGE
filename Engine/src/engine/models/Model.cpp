#pragma once
#include <engine/models/Model.h>

Model::Model(Mesh* mesh, Texture* diffuseTex, Texture* specularTex, Material* material) {
	this->mesh = mesh;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
	this->material = material;
}
Model::~Model() { }

Mesh* Model::getMesh() { return mesh; }

Texture* Model::getDiffuseTex()  { return diffuseTex;  }
Texture* Model::getSpecularTex() { return specularTex; }

Material* Model::getMaterial() { return material; }