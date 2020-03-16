#pragma once
#include "../../libs.h"

class Light {
	protected:
		glm::vec3 position;
		glm::vec3 color;


	public:
		Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.f));
		virtual ~Light();

		void setPosition(glm::vec3 position);
		void setColor(glm::vec3 color);

		glm::vec3 getPosition();
		glm::vec3 getColor();
};

class LightPoint : public Light {
	private:
		float attenuation;
		float falloffNear, falloffFar;


	public:
		LightPoint(glm::vec3 position, glm::vec3 color = glm::vec3(1.f), float attenuation = 1.f, float falloffNear = 0.f, float falloffFar = 1.f);
		~LightPoint();

		void setAttenuation(float attenuation);
		void setFalloffNear(float falloffNear);
		void setFalloffFar(float falloffFar);

		float getAttenuation();
		float getFalloffNear();
		float getFalloffFar();
};