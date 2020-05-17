#pragma once
#include "Camera3D_Player3rd.h"

void Camera3D_Player::calcPosition(float horizDistance, float vertDistance) {
	float angle = player.getRotation().y + angleAroundPlayer;
	float angleRads = (angle * PI) / 180.f;
	float offsetX = horizDistance * sin(angleRads);
	float offsetZ = horizDistance * cos(angleRads);
	glm::vec3 playerPos = player.getPosition();
	position = glm::vec3(
		playerPos.x - offsetX,
		playerPos.y + vertDistance,
		playerPos.z - offsetZ
	);
}

void Camera3D_Player::updatePosition() {
	calcPosition(calcHorizontalDistance(), calcVerticalDistance());
	yaw = 270.f - (player.getRotation().y + angleAroundPlayer); // 270 should be 180, but due to some prev calc its this way (need to check)
}