#pragma once
#include "../../libs.h"
#include "../Shader.h"

class MaterialUI {
	private:
		glm::vec3 color;
		GLint diffuseTex;
		GLint maskTex;


	public:
		MaterialUI(GLint diffuseTex, glm::vec3 color = glm::vec3(1.f), GLint maskTex = -1);
		~MaterialUI();

		void sendToShader(Shader &program);
};