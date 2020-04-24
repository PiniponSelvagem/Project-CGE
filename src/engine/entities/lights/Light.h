#pragma once
#include "../../../libs.h"
#include "../../shaders/Shader.h"

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
		void serIntensity(const float intensity);

		/*
		glm::vec3 getPosition();
		glm::vec3 getColor();
		float getIntensity();
		*/

		virtual void sendToShader(Shader &program) = 0;
};

class LightPoint : public Light {
	protected:
		float attenuation;
		float falloffNear, falloffFar;


	public:
		LightPoint(glm::vec3 position, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f, float attenuation = 1.f, float falloffNear = 0.f, float falloffFar = 1.f);
		~LightPoint();

		void setAttenuation(float attenuation);
		void setFalloffNear(float falloffNear);
		void setFalloffFar(float falloffFar);

		/*
		float getAttenuation();
		float getFalloffNear();
		float getFalloffFar();
		*/

		void sendToShader(Shader &program);
};