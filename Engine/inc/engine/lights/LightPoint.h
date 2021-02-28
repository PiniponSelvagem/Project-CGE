#pragma once
#include <engine/lights/Light.h>

class LightPoint : public Light {
	protected:
		float attenuation;
		float falloffNear, falloffFar;


	public:
		LightPoint(glm::vec3 position, glm::vec3 color = glm::vec3(1.f),
				   float intensity = 1.f, float attenuation = 1.f,
				   float falloffNear = 0.f, float falloffFar = 1.f
		);
		virtual ~LightPoint();

		void setAttenuation(float attenuation);
		void setFalloffNear(float falloffNear);
		void setFalloffFar(float falloffFar);

		float getAttenuation();
		float getFalloffNear();
		float getFalloffFar();
};