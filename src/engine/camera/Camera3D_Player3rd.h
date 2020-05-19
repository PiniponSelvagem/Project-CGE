#pragma once
#include "Camera3D.h"
#include <math.h>

#include "../entities/player/Player.h"

class Camera3D_Player : public Camera3D {
	private:
		Player& player;
		float playerViewHeight;

		float distFromPlayer, maxDistFromPlayer;
		float angleAroundPlayer;
		
		inline float calcHorizontalDistance() { return distFromPlayer * cos(glm::radians(pitch)); }
		inline float calcVerticalDistance()   { return distFromPlayer * sin(glm::radians(pitch)); }

		void calcPosition(float horizDistance, float vertDistance);


	public:
		Camera3D_Player(Player& player, float playerViewHeight, float distToPlayer, float maxDistFromPlayer, float angleAroundPlayer, float startAngleToPlayer,
						float fov, float nearPlane, float farPlane)
			: Camera3D(fov, nearPlane, farPlane, glm::vec3(0.f), glm::vec3(0.f, startAngleToPlayer, 0.f)),
			player(player), playerViewHeight(playerViewHeight), distFromPlayer(-distToPlayer), maxDistFromPlayer(-maxDistFromPlayer), angleAroundPlayer(angleAroundPlayer)
		{ }
		virtual ~Camera3D_Player() { }

		void updatePosition();

		inline void changeDistanceFromPlayer(float distance) { distFromPlayer += distance * 0.25f; }
		inline void changePitch(float pitch)                 { setPitch(this->pitch += pitch); }
		inline void changeAngleAroundPlayer(float yawOffset) {
			angleAroundPlayer -= yawOffset;

			if (angleAroundPlayer > 360.f || angleAroundPlayer < -360.f)
				angleAroundPlayer = 0.f;
		}

		void changePlayerDirection(float yawOffset);
};