#pragma once
#include "../../engine/scene/Scene.h"

class PerformanceTest : public Scene {
	private:
		void initShaders();
		void initMeshes();
		void initTextures();
		void initMaterials();
		void initModels();
		void initEntities();
		void initLights();
		void initEnviroment();

	public:
		PerformanceTest();
		~PerformanceTest();

		void update(float dTime);

		/* TODO: Make Player class??? */
		void cameraPanTilt(double mouseOffsetX, double mouseOffsetY);
		void cameraFoward(float dTime);
		void cameraBackward(float dTime);
		void cameraLeft(float dTime);
		void cameraRight(float dTime);
		void cameraUp(float dTime);
		void cameraDown(float dTime);

		void lightSetPosition() { }
		/******************************/
};

