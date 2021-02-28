#pragma once
#include <engine/entities/player/Player.h>
#include <math.h>


Player::Player(float runSpeed, float turnSpeed, float gravity, float jumpPower,
			   Model* model, glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale
) : Entity(model, position, origin, rotation, scale) {
	this->runSpeed = runSpeed;
	this->turnSpeed = turnSpeed;
	this->gravity = gravity;
	this->jumpPower = jumpPower;
}
Player::~Player() { }

void Player::setRunSpeed(float speed) {
	this->runSpeed = speed;
}
void Player::setTurnSpeed(float speed) {
	this->turnSpeed = speed;
}
void Player::setGravity(float gravity) {
	this->gravity = gravity;
}
void Player::setJumpPower(float jumpPower) {
	this->jumpPower = jumpPower;
}

void Player::move(float dTime, Terrain& terrain) {
	changeRotation(glm::vec3(0, currTurnSpeed * dTime, 0));

	currJumpSpeed += gravity * dTime;
	changePosition(glm::vec3(0, currJumpSpeed * dTime, 0));
	float terrainHeight = terrain.getHeight(getPosition().x, getPosition().z);
	if (getPosition().y < terrainHeight) {
		currJumpSpeed = 0.f;
		inAir = false;
		setPositionY(terrainHeight);
	}

	float distance = currSpeed * dTime;
	float radiansY = glm::radians(getRotation().y);

	float dX = distance * sin(radiansY);
	float dZ = distance * cos(radiansY);

	changePosition(glm::vec3(dX, 0, dZ));

	currSpeed = 0;
	currTurnSpeed = 0;
}

void Player::moveFoward()   { currSpeed += runSpeed;  }
void Player::moveBackward() { currSpeed += -runSpeed; }

void Player::rotateLeft()  { currTurnSpeed += turnSpeed;  }
void Player::rotateRight() { currTurnSpeed += -turnSpeed; }

void Player::jump() {
	if (!inAir) {
		currJumpSpeed = jumpPower;
		inAir = true;
	}
}