#pragma once
#include "Player.h"
#include <math.h>
#define PI 3.1459

void Player::move(float dTime) {
	changeRotation(glm::vec3(0, currTurnSpeed * dTime, 0));

	currJumpSpeed += gravity * dTime;
	changePosition(glm::vec3(0, currJumpSpeed * dTime, 0));
	if (getPosition().y < terrainHeight) {
		currJumpSpeed = 0.f;
		inAir = false;
		setPositionY(terrainHeight);
	}

	float distance = currSpeed * dTime;
	float radiansY = (getRotation().y * PI) / 180.f;
	float dX = distance * sin(radiansY);
	float dZ = distance * cos(radiansY);

	changePosition(glm::vec3(dX, 0, dZ));

	currSpeed = 0;
	currTurnSpeed = 0;
}