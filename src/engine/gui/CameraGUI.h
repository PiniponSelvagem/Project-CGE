#pragma once
#include "../../libs.h"

class CameraGUI {
	protected:
		float width, height;
		float farPlane;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		void updateProjectionMatrix();


	public:
		CameraGUI(float width, float height, float farPlane);
		~CameraGUI();

		const glm::mat4 getViewMatrix();
		const glm::mat4 getProjectionMatrix();

		void setGuiSize(float width, float height);
};
