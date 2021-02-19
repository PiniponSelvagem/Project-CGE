#pragma once
#include <engine/entities/player/Player.h>
#include <math.h>

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