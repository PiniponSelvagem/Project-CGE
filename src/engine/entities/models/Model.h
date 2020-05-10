#pragma once
#include "../../../libs.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
	private:
		Mesh &mesh;
		Texture &diffuseTex, &specularTex;
		Material &material;


	public:
		Model(Mesh &mesh, Texture &diffuseTex, Texture &specularTex, Material &material)
			: mesh(mesh), diffuseTex(diffuseTex), specularTex(specularTex), material(material)
		{ }
		virtual ~Model() { }

		inline Mesh& getMesh() const { return mesh; }

		inline Texture& getDiffuseTex() const  { return diffuseTex; }
		inline Texture& getSpecularTex() const { return specularTex; }

		inline Material& getMaterial() const { return material; }

};