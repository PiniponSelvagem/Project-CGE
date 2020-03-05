#pragma once
#include "../libs.h"

class Light {
	private:
		glm::vec3 position;
		glm::vec3 color;



	public:
		Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.f));
		~Light();

		void setPosition(glm::vec3 position);
		void setColor(glm::vec3 color);

		glm::vec3 getPosition();
		glm::vec3 getColor();
};

