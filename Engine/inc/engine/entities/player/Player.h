#pragma once
#include <engine/entities/Entity.h>
#include <engine/terrains/Terrain.h>

class Player : public Entity {
	private:
		float runSpeed;
		float turnSpeed;
		float gravity;
		float jumpPower;
		
		float currSpeed = 0;
		float currTurnSpeed = 0;
		float currJumpSpeed = 0;

		bool inAir = false;


	public:
		Player(float runSpeed, float turnSpeed, float gravity, float jumpPower,
			   Model* model, glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f)
		);
		virtual ~Player();

		void setRunSpeed(float speed);
		void setTurnSpeed(float speed);
		void setGravity(float gravity);
		void setJumpPower(float jumpPower);
		

		void move(float dTime, Terrain& terrain);

		void moveFoward();
		void moveBackward();

		void rotateLeft();
		void rotateRight();

		void jump();
};