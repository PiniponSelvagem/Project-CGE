#pragma once
#include <engine/Libs.h>
#include <engine/shaders/Shader.h>

class Fog {
	private:
		float density;
		float gradient;

	public:
		Fog(float density, float gradient);
		virtual ~Fog();

		void setDensity(float density);
		void setGradient(float gradient);

		float getDensity();
		float getGradient();
};

