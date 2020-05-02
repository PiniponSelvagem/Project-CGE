#pragma once
#include "../../libs.h"
#include "../shaders/Shader.h"

class Fog {
	private:
		float density;
		float gradient;

	public:
		Fog(float density, float gradient) {
			this->density = density;
			this->gradient = gradient;
		}
		~Fog() { }

		inline void setDensity(float density) { this->density = density; }
		inline void setGradient(float gradient) { this->gradient = gradient; }

		void sendToShader(Shader &program) {
			program.set1f(density,  "fog.density");
			program.set1f(gradient, "fog.gradient");
		}
};

