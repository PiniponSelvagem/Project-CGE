#pragma once
#include "../../libs.h"

class CameraUI {
	protected:
		float width, height;
		float farPlane;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		void updateProjectionMatrix();


	public:
		CameraUI(float width, float height, float farPlane);
		~CameraUI();

		const glm::mat4 getViewMatrix();
		const glm::mat4 getProjectionMatrix();

		void setUIWindowSize(float width, float height);
};
