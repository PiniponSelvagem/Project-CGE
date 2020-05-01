#pragma once
#include "../../libs.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

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

		void changePanTilt(const float &dTime, const double &offsetX, const double &offsetY);
};

class Camera2D : public Camera {
	private:
		void updateCameraVectors();


	public:
		Camera2D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction);
		~Camera2D();

		void updateProjectionMatrix();
};
class Camera3D : public Camera {
	private:
		void updateCameraVectors();


	public:
		Camera3D(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction);
		~Camera3D();

		void updateProjectionMatrix();
};