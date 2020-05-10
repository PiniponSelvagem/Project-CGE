#pragma once
#include "../../libs.h"
#include <map>

#include "../entities/models/Entity.h"

// This struct is used to compare entities in a map
struct mCompare {
	public:
		bool operator() (const Model& t1, const Model& t2) const {
			return (
				(t1.getMesh().getVaoID() < t2.getMesh().getVaoID())			||
				(t1.getSpecularTex().getID() < t2.getSpecularTex().getID())	||
				(t1.getDiffuseTex().getID() < t2.getDiffuseTex().getID())
			);
		}
};
typedef std::map<Model, std::vector<Entity>, mCompare> modelEntity_map;


class EntityRenderer {
	private:
		Shader* shader;

		void bindModel(Model &model);
		void bindTexture(Texture &texture, int textureUnit);
		void renderEntity(Entity &entity, int nVertices, int nIndices);
		void unbindModel();


	public:
		EntityRenderer(Shader* shader) : shader(shader) { }

		void render(modelEntity_map &entities);
};