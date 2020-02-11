#pragma once

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT };

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


		void updateCameraVectors() {
			front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));

			front = glm::normalize(front);
			right = glm::normalize(glm::cross(front, worldUp));
			up    = glm::normalize(glm::cross(right, front));
		}



	public:
		Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp) {
			//viewMatrix = glm::mat4(1.f);
			movementSpeed = 3.f;
			sensivity = 5.f;
			this->position = position;
			this->right = glm::vec3(0.f);
			this->worldUp = worldUp;

			pitch = 0.f;
			yaw = -90.f;
			roll = 0.f;

			updateCameraVectors();
		}

		~Camera() {

		}

		const glm::mat4 getViewMatrix() {
			updateCameraVectors();
			viewMatrix = glm::lookAt(position, position + front, up);
			return viewMatrix;
		}

		const glm::vec3 getPosition() {
			return position;
		}



		void move(const float &dTime, const int direction) {
			switch (direction) {
			case FORWARD:
				position += front * movementSpeed * dTime;
				break;
			case BACKWARD:
				position -= front * movementSpeed * dTime;
				break;
			case LEFT:
				position -= right * movementSpeed * dTime;
				break;
			case RIGHT:
				position += right * movementSpeed * dTime;
				break;
			}
		}

		void updateMouseInput(const float &dTime, const double &offsetX, const double &offsetY) {
			pitch += static_cast<GLfloat>(offsetY) * sensivity * dTime;
			yaw   += static_cast<GLfloat>(offsetX) * sensivity * dTime;

			if (pitch > 80.f)
				pitch = 80.f;
			else if (pitch < -80.f)
				pitch = -80.f;			

			if (yaw > 360.f || yaw < -360.f)
				yaw = 0.f;

			std::cout << "pitch: " << pitch << " yaw: " << yaw << std::endl;
		}

		void updateInput(const float &dTime, const int direction, const double &offsetX, const double &offsetY) {
			updateMouseInput(dTime, offsetX, offsetY);
		}
};