#pragma once
#include <engine/shaders/Shader.h>

#include <engine/camera/Camera.h>


class UIShader : public Shader {
	public:
		UIShader(const char* vertexFile, const char* fragmentFile)
			: Shader(vertexFile, fragmentFile)
		{ }
		virtual ~UIShader() { }

		void sendModelMatrix(glm::mat4& modelMatrix);
};