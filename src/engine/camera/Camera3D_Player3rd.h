#pragma once
#include "Camera3D.h"
#include <math.h>
#define PI 3.1459

#include "../entities/player/Player.h"

class Camera3D_Player : public Camera3D {
	private:
		Player& player; 

		float distFromPlayer;
		float angleAroundPlayer;
		
		inline float calcHorizontalDistance() { return distFromPlayer * cos((pitch * PI) / 180.f); }
		inline float calcVerticalDistance()   { return distFromPlayer * sin((pitch * PI) / 180.f); }

		void calcPosition(float horizDistance, float vertDistance);


	public:
		Camera3D_Player(Player& player, float distToPlayer, float angleAroundPlayer,
						float fov, float nearPlane, float farPlane, float startAngleToPlayer)
			: Camera3D(fov, nearPlane, farPlane, glm::vec3(0.f), glm::vec3(startAngleToPlayer, 0.f, 0.f)),
			player(player), distFromPlayer(distToPlayer), angleAroundPlayer(angleAroundPlayer)
		{ }
		virtual ~Camera3D_Player() { }

		void updatePosition();

		inline void changeDistanceFromPlayer(float distance) { distFromPlayer -= distance; }
		inline void changePitch(float pitch)                 { this->pitch += pitch; }
		inline void changeAngleAroundPlayer(float angle)     { angleAroundPlayer -= angle; }
};