#include "libs.h"
#include "game/Game.h"

#if defined _WIN32
#include <Windows.h>
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif


// SETTINGS
const unsigned int GL_MAJOR_VER = 4;
const unsigned int GL_MINOR_VER = 4;
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

const float FOV = 90.f;


int main() {
	Game game("Project-CGE", SCR_WIDTH, SCR_HEIGHT, true);
	
	game.initInput();

	game.loadScene();
	game.loadSceneUI();

	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
	}

	return 0;
}