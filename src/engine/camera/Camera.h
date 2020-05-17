#pragma once
#include "../../libs.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

#define BASE_SENSIVITY 0.01
#define MAX_PITCH 89.9f	// Supported range: [0, 89.9]. Values outside this range might have unexpected behavior.

class Camera {
	protected:
		float aspectRatio = 1.333f; // 1.333 -> 4:3

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		float fov;
		float nearPlane;
		float farPlane;

		GLfloat movementSpeed;
		GLfloat sensivity;

		glm::vec3 worldUp;
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 up;

		GLfloat pitch;
		GLfloat yaw;
		GLfloat roll;

		virtual void updateCameraVectors() = 0;

		inline void setPitch(GLfloat pitch) {
			this->pitch = pitch;

			if (this->pitch > MAX_PITCH)
				this->pitch = MAX_PITCH;
			else if (this->pitch < -MAX_PITCH)
				this->pitch = -MAX_PITCH;
		}
		inline void setYaw(GLfloat yaw) {
			this->yaw = yaw;

			if (this->yaw > 360.f || this->yaw < -360.f)
				this->yaw = 0.f;
		}


	public:
		Camera(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction);
		virtual ~Camera();

		const glm::mat4 getViewMatrix();
		const glm::mat4 getProjectionMatrix();
		const glm::vec3 getPosition();

		void setAspectRatio(float aspectRatio);
		virtual void updateProjectionMatrix() = 0;

		void setPosition(glm::vec3 position);
		void moveFly(const float &dTime, const int direction);
		void moveWalk(const float &dTime, const int direction);
		
		void changePanTilt(const double &offsetX, const double &offsetY);
};
