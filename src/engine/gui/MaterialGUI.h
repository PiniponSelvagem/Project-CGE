#pragma once
#include "../../libs.h"
#include "../Shader.h"

class MaterialGUI {
	private:
		glm::vec3 color;
		GLint diffuseTex;
		GLint maskTex;


	public:
		MaterialGUI(GLint diffuseTex, glm::vec3 color = glm::vec3(1.f), GLint maskTex = -1);
		~MaterialGUI();

		void sendToShader(Shader &program);
};