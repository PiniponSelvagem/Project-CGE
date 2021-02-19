#pragma once
#include <engine/Libs.h>
#include <engine/shaders/Shader.h>

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

		inline float getDensity()   { return density; }
		inline float getGradient() { return gradient; }
};

