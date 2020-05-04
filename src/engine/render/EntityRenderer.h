#pragma once
#include "../../libs.h"

#include "MasterRenderer.h"
#include "../entities/models/Entity.h"

class EntityRenderer : public MasterRenderer {
	private:
		void bindTexture(Texture* texture, int textureUnit);

	public:
		EntityRenderer(Shader* shader) : MasterRenderer(shader) { }

		void render(Entity* entity);
};