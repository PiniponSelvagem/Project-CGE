#pragma once
#include "Camera.h"

class Camera2D : public Camera {
	public:
		Camera2D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction);
		virtual ~Camera2D() { }

		void updateProjectionMatrix();
};