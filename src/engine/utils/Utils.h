#pragma once
#include <GLM/glm.hpp>

class Utils {
	public:
		static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};