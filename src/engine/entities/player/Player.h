#pragma once
#include "../Entity.h"

class Player : public Entity {
	private:
		const float runSpeed;
		const float turnSpeed;
		const float gravity;
		const float jumpPower;

		const float terrainHeight = 0.f;

		float currSpeed = 0;
		float currTurnSpeed = 0;
		float currJumpSpeed = 0;

		bool inAir = false;


	public:
		Player(float runSpeed, float turnSpeed, float gravity, float jumpPower,
			Model* model, glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f)
		)
			: runSpeed(runSpeed), turnSpeed(turnSpeed), gravity(gravity), jumpPower(jumpPower),
			Entity(model, position, origin, rotation, scale)
		{ }
		virtual ~Player() { }
		
		void move(float dTime);

		inline void setMoveFoward()   { currSpeed += runSpeed;  }
		inline void setMoveBackward() { currSpeed += -runSpeed; }

		inline void setRotateLeft()  { currTurnSpeed += turnSpeed;  }
		inline void setRotateRight() { currTurnSpeed += -turnSpeed; }

		inline void setJump() {
			if (!inAir) {
				currJumpSpeed = jumpPower;
				inAir = true;
			}
		}
};