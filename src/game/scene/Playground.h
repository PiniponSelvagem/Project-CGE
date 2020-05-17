#pragma once
#include "../../engine/scene/Scene.h"

#include "../../engine/camera/Camera3D_Player3rd.h"

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
		Playground() : Scene() { }
		virtual ~Playground() { }

		void update(float dTime);

		void cameraPanTilt(double mouseOffsetX, double mouseOffsetY);
		void playerFoward();
		void playerBackward();
		void playerLeft();
		void playerRight();
		void playerJump();
		
		void cameraZoom(float zoom);
		void cameraPith(float pitch);
		void cameraYaw(float yaw);

		//void lightSetPosition();
};

