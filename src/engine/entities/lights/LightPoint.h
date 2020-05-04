#pragma once
#include "Light.h"

class LightPoint : public Light {
	protected:
		float attenuation;
		float falloffNear, falloffFar;


	public:
		LightPoint(glm::vec3 position, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f, float attenuation = 1.f, float falloffNear = 0.f, float falloffFar = 1.f) 
		: Light(position, color, intensity) {
			this->attenuation = attenuation;
			this->falloffNear = falloffNear;
			this->falloffFar = falloffFar;
		}
		~LightPoint() { }

		void setAttenuation(float attenuation) {
			if (attenuation < 0.f) {
				this->attenuation = 0.f;
				return;
			}
			this->attenuation = attenuation;
		}
		void setFalloffNear(float falloffNear) {
			if (falloffNear < 0.f) {
				this->falloffNear = 0.f;
				return;
			}
			this->falloffNear = falloffNear;
		}
		void setFalloffFar(float falloffFar) {
			if (falloffFar < falloffNear) {
				this->falloffFar = falloffNear;
				return;
			}
			this->falloffFar = falloffNear;
		}

		inline float getAttenuation() { return attenuation; }
		inline float getFalloffNear() { return falloffNear; }
		inline float getFalloffFar()  { return falloffFar; }
};