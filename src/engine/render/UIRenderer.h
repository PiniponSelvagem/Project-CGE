#pragma once
#include "../../libs.h"

#include "../ui/UI.h"
#include "../models/Mesh.h"
#include "../shaders/UIShader.h"

class UIRenderer {
	private:
		Mesh* quad;
		UIShader shader;

	public:
		UIRenderer(const char* vertexFile, const char* fragFile);
		virtual ~UIRenderer() {
			delete quad;
		}

		void render(std::vector<UI*> uis);

		void reloadShader() { shader.reload(); }
};