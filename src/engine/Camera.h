#pragma once
#include "../libs.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
	private:
		bool is3D;

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


		void updateCameraVectors();



	public:
		Camera(float fov, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 direction, bool is3D);
		~Camera();

		const glm::mat4 getViewMatrix();
		const glm::mat4 getProjectionMatrix();
		const glm::vec3 getPosition();

		void updateProjectionMatrix(float aspectRatio);

		void move(const float &dTime, const int direction);

		void updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY);
		void updateInput(const float &dTime, const int direction, const double &offsetX, const double &offsetY);
};