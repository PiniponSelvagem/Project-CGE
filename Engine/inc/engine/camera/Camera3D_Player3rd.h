#pragma once
#include <engine/camera/Camera3D.h>
#include <math.h>

#include <engine/entities/player/Player.h>

class Camera3D_Player3rd : public Camera3D {
	private:
		Player* player;
		float playerViewHeight;

		float distFromPlayer, maxDistFromPlayer;
		float angleAroundPlayer;
		

		float calcHorizontalDistance();
		float calcVerticalDistance();

		void calcPosition(float horizDistance, float vertDistance);


	public:
		Camera3D_Player3rd(Player* player, float playerViewHeight, float distToPlayer, float maxDistFromPlayer, float startYawToPlayer, float startPitchToPlayer,
						   float fov, float nearPlane, float farPlane);
		virtual ~Camera3D_Player3rd();

		void updatePosition();

		void changeDistanceFromPlayer(float distance);
		void changePitch(float pitch);
		void changeAngleAroundPlayer(float yawOffset);

		void changePlayerDirection(float yawOffset);
};