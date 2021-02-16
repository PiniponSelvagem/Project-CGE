#pragma once
#include "UI.h"

void UI::updateModelMatrix() {
	if (modelUpdated) {
		Maths::updateModelMatrix(
			&modelMatrix,
			glm::vec3(position, 0.f),
			glm::vec3(rotation, 0.f, 0.f),
			glm::vec3(scale, 0.f),
			glm::vec3(origin, 0.f)
		);
		modelUpdated = false;
	}
};
