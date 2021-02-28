#pragma once
#include <engine/Libs.h>

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

#define BASE_SENSIVITY 0.01
#define MAX_PITCH 89.9f	// Supported range: [-89.9f, 89.9]. Values outside this range might have unexpected behavior.

class Camera {
	protected:
		float aspectRatio = 1.333f; // 1.333 -> 4:3

		glm::mat4 viewMatrix = glm::mat4(0.f);
		glm::mat4 projectionMatrix = glm::mat4(0.f);
		float fov;
		float nearPlane;
		float farPlane;

		GLfloat movementSpeed = 0;
		GLfloat sensivity = 0;

		glm::vec3 position = glm::vec3(0.f);
		glm::vec3 worldUp = glm::vec3(0.f);
		glm::vec3 front = glm::vec3(0.f);
		glm::vec3 right = glm::vec3(0.f);
		glm::vec3 up = glm::vec3(0.f);

		GLfloat yaw;
		GLfloat pitch;
		GLfloat roll;		// currently not supported

		/**
		 * @brief Set camera pitch in degrees.
		 * @param pitch Camera new pitch, value range [-89.9f, 89.9f]
		*/
		void setPitch(GLfloat pitch);
		void setYaw(GLfloat yaw);

		virtual void updateCameraVectors();


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
		
		void changePanTilt(const float &offsetX, const float&offsetY);
};
