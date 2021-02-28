#pragma once
#include <engine/Libs.h>
#include <engine/models/Vertex.h>
#include <engine/models/Mesh.h>
#include <engine/models/Texture.h>
#include <engine/models/Material.h>

class Model {
	private:
		Mesh* mesh;
		Texture* diffuseTex, *specularTex;
		Material* material;


	public:
		Model(Mesh* mesh, Texture* diffuseTex, Texture* specularTex, Material* material);
		virtual ~Model();

		Mesh* getMesh();

		Texture* getDiffuseTex();
		Texture* getSpecularTex();

		Material* getMaterial();

};