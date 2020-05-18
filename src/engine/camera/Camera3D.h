#pragma once
#include "Camera.h"

class Camera3D : public Camera {
	public:
		Camera3D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction);
		virtual ~Camera3D() { }

		void updateProjectionMatrix();
};