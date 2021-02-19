#pragma once
#include <engine/camera/Camera3D_Player3rd.h>

void Camera3D_Player3rd::calcPosition(float horizDistance, float vertDistance) {
	float angle = player.getRotation().y + angleAroundPlayer;
	float angleRads = glm::radians(angle);
	float offsetX = horizDistance * sin(angleRads);
	float offsetZ = horizDistance * cos(angleRads);

	glm::vec3 playerPos = player.getPosition();
	position = glm::vec3(
		playerPos.x - offsetX,
		playerPos.y + vertDistance,
		playerPos.z - offsetZ
	);
}

void Camera3D_Player3rd::updatePosition() {
	if (distFromPlayer > 0) distFromPlayer = 0;
	else if (distFromPlayer < maxDistFromPlayer) distFromPlayer = maxDistFromPlayer;
	calcPosition(calcHorizontalDistance(), calcVerticalDistance() + playerViewHeight);
	yaw = -90.f - (player.getRotation().y + angleAroundPlayer); // 180 in ThinMatrix tutorial
}


void Camera3D_Player3rd::changePlayerDirection(float yawOffset) {
	angleAroundPlayer = 180.f;
	player.changeRotation(glm::vec3(0, -yawOffset, 0));
}