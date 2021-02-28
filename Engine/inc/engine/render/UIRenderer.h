#pragma once
#include <engine/Libs.h>

#include <engine/ui/UI.h>
#include <engine/models/Mesh.h>
#include <engine/shaders/UIShader.h>

class UIRenderer {
	private:
		Mesh* quad;
		UIShader shader;

	public:
		UIRenderer(const char* vertexFile, const char* fragFile);
		virtual ~UIRenderer();

		void reloadShader();

		void render(std::vector<UI*> uis);
};