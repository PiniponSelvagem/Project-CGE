#pragma once
#include "../libs.h"
#include "../engine/Engine.h"

class Game : public Engine {
	private:
		void updateMouseInput();
		void updateKeyboardInput();
		

	public:
		Game(const char* title, const int width, const int height, bool resizable);
		~Game();

		void initInput();

		void loadScene();
		void loadSceneUI();
};

