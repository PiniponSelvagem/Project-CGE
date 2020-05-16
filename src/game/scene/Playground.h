#pragma once
#include "../../engine/scene/Scene.h"

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

	public:
		Playground();
		~Playground();

		void update(float dTime);

		/* TODO: Make Player class??? */
		void cameraPanTilt(double mouseOffsetX, double mouseOffsetY);
		void playerFoward();
		void playerBackward();
		void playerLeft();
		void playerRight();
		void playerJump();
		void cameraDown(float dTime);

		void lightSetPosition();
		/******************************/
};

