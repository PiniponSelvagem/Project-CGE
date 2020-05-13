#pragma once
#include "../../libs.h"

#include "../entities/models/Entity.h"

class EntityRenderer {
	private:
		Shader& shader;

		void bindTexture(Texture* texture, int textureUnit);

	public:
		EntityRenderer(Shader& shader) : shader(shader) { }

		Shader &getShader() { return shader; }

		void render(Entity* entity);
};