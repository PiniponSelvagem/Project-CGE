#pragma once
#include <engine/scene/Scene.h>
#include <engine/camera/Camera3D_Player3rd.h>

class Playground : public Scene {
	private:
		void initRenderer();
		void initMeshes();
		void initTextures();
		void initMaterials();
		void initModels();
		void initEntities();
		void initLights();
		void initEnviroment();
		void initCamera();

	public:
		Playground() : Scene("resources/scenes/playground.scene") { }
		virtual ~Playground() { }

		void update(float dTime);

		void cameraPanTilt(double mouseOffsetX, double mouseOffsetY);
		void playerFoward();
		void playerBackward();
		void playerLeft();
		void playerRight();
		//void playerStrafeLeft();
		//void playerStrafeRight();
		void playerJump();
		
		void cameraZoom(float zoomOffset);
		void cameraPith(float pitchOffset);
		void cameraYaw(float yawOffset);
		void cameraSetPlayerDirection(float yawOffset);

		void lightSetPosition();
		/*
		void cameraFoward(float dTime);
		void cameraBackward(float dTime);
		void cameraLeft(float dTime);
		void cameraRight(float dTime);
		void cameraUp(float dTime);
		void cameraDown(float dTime);
		*/
};

