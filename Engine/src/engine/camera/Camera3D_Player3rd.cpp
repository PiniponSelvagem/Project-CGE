#pragma once
#include <engine/camera/Camera3D_Player3rd.h>

float Camera3D_Player3rd::calcHorizontalDistance() { 
	return distFromPlayer * cos(glm::radians(pitch));
}
float Camera3D_Player3rd::calcVerticalDistance() {
	return distFromPlayer * sin(glm::radians(pitch));
}

void Camera3D_Player3rd::calcPosition(float horizDistance, float vertDistance) {
	float angle = player->getRotation().y + angleAroundPlayer;
	float angleRads = glm::radians(angle);
	float offsetX = horizDistance * sin(angleRads);
	float offsetZ = horizDistance * cos(angleRads);

	glm::vec3 playerPos = player->getPosition();
	position = glm::vec3(
		playerPos.x - offsetX,
		playerPos.y + vertDistance,
		playerPos.z - offsetZ
	);
}



Camera3D_Player3rd::Camera3D_Player3rd(Player* player, float playerViewHeight, float distToPlayer, float maxDistFromPlayer, float startYawToPlayer, float startPitchToPlayer,
									   float fov, float nearPlane, float farPlane
) : Camera3D(fov, nearPlane, farPlane, glm::vec3(0.f), glm::vec3(0.f, startPitchToPlayer, 0.f)) {
	this->player = player;
	this->playerViewHeight = playerViewHeight;
	this->distFromPlayer = -distToPlayer;
	this->maxDistFromPlayer = -maxDistFromPlayer;
	this->angleAroundPlayer = startYawToPlayer;
}
Camera3D_Player3rd::~Camera3D_Player3rd() { }

void Camera3D_Player3rd::updatePosition() {
	if (distFromPlayer > 0) distFromPlayer = 0;
	else if (distFromPlayer < maxDistFromPlayer) distFromPlayer = maxDistFromPlayer;
	calcPosition(calcHorizontalDistance(), calcVerticalDistance() + playerViewHeight);
	yaw = -90.f - (player->getRotation().y + angleAroundPlayer); // 180 in ThinMatrix tutorial
}

void Camera3D_Player3rd::changeDistanceFromPlayer(float distance) {
	distFromPlayer += distance * 0.25f;
}
void Camera3D_Player3rd::changePitch(float pitch) {
	setPitch(this->pitch += pitch);
}
void Camera3D_Player3rd::changeAngleAroundPlayer(float yawOffset) {
	angleAroundPlayer -= yawOffset;
	angleAroundPlayer = fmod(angleAroundPlayer, 360.f);
}

void Camera3D_Player3rd::changePlayerDirection(float yawOffset) {
	angleAroundPlayer = 180.f;
	player->changeRotation(glm::vec3(0, -yawOffset, 0));
}