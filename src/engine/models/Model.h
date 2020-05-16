#pragma once
#include "../../libs.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
	private:

		/*
			TODO:
			maybe use reference instead of pointers

			check possible other places too
		*/
		Mesh* mesh;
		Texture* diffuseTex, *specularTex;
		Material* material;


	public:
		Model(Mesh* mesh, Texture* diffuseTex, Texture* specularTex, Material* material)
			: mesh(mesh), diffuseTex(diffuseTex), specularTex(specularTex), material(material)
		{ }
		virtual ~Model() { }

		inline Mesh* getMesh() { return mesh; }

		inline Texture* getDiffuseTex()  { return diffuseTex; }
		inline Texture* getSpecularTex() { return specularTex; }

		inline Material* getMaterial() { return material; }

};