#pragma once
#include "../../libs.h"
#include "../shaders/Shader.h"

/*
	NOTE:

	Maybe the names:
		attenuation
		falloffNear
		falloffFar

	Arent the right names for their purpose.
	Saw some sugested names:
		constant
		linear
		quadratic

	But untill adding a run-time light edit mode, will stay this way.
*/


class Light {
	protected:
		glm::vec3 position;
		glm::vec3 color;
		float intensity;


	public:
		Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f) {
			this->position = position;
			this->color = color;
			this->intensity = intensity;
		}
		virtual ~Light() { }

		inline void setPosition(const glm::vec3 position) { this->position = position; }
		inline void setColor(const glm::vec3 color)       { this->color = color; }
		inline void serIntensity(const float intensity)   { this->intensity = intensity; }

		inline glm::vec3 getPosition() { return position; }
		inline glm::vec3 getColor()    { return color; }
		inline float getIntensity()    { return intensity; }
};