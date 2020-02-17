#pragma once
#include "../libs.h"

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
	private:
		glm::mat4 viewMatrix;

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
		Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
		~Camera();

		const glm::mat4 getViewMatrix();

		const glm::vec3 getPosition();



		void move(const float &dTime, const int direction);

		void updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY);
		void updateInput(const float &dTime, const int direction, const double &offsetX, const double &offsetY);
};