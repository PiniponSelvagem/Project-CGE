#pragma once
#include "../../engine/scene/Scene.h"

class HudTest : public Scene {
	private:
		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initLights();

	public:
		HudTest();
		~HudTest();

		void update();
};

