#pragma once
#include <engine/Libs.h>
#include <engine/shaders/Shader.h>

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
		Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f);
		virtual ~Light();

		void setPosition(const glm::vec3 position);
		void setColor(const glm::vec3 color);
		void setIntensity(const float intensity);

		glm::vec3 getPosition();
		glm::vec3 getColor();
		float getIntensity();
};