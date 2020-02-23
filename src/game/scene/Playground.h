#pragma once
#include "../../engine/scene/Scene.h"

class Playground : public Scene {
	private:
		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initLights();

	public:
		Playground();
		~Playground();

		void update();

		/* TODO: Make Player class??? */
		void cameraPanTilt(float dTime, float mouseOffsetX, float mouseOffsetY);
		void cameraFoward(float dTime);
		void cameraBackward(float dTime);
		void cameraLeft(float dTime);
		void cameraRight(float dTime);
		void cameraUp(float dTime);
		void cameraDown(float dTime);
		/******************************/
};

