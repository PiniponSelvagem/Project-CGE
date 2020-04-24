#pragma once
#include "../../libs.h"
#include "../shaders/Shader.h"

class Fog {
	private:
		float density;
		float gradient;

	public:
		Fog(float density, float gradient);
		~Fog();

		void setDensity(float density);
		void setGradient(float gradient);

		void sendToShader(Shader &program);
};

