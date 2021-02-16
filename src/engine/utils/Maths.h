#pragma once
#include "../../libs.h"

class Maths {
	public:
		static void updateModelMatrix(glm::mat4 *modelMatrix, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin);
};