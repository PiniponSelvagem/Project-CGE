#pragma once
#include "../../libs.h"

#include "MasterRenderer.h"
#include "../entities/models/Entity.h"

class EntityRenderer : public MasterRenderer {
	public:
		EntityRenderer(Shader* shader) : MasterRenderer(shader) { }

		void render(Entity* entity);
};