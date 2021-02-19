#include <engine/libs.h>
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
const unsigned int SCR_WIDTH  = 1280;
const unsigned int SCR_HEIGHT = 720;

const float FOV = 90.f;


int main() {
	Game game("Project-CGE", SCR_WIDTH, SCR_HEIGHT, true);
	
	game.initInput();

	game.loadScene();

	/* Measure speed */
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (!game.getWindowShouldClose()) {
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			int fps = 1 / (1/double(nbFrames));

			// printf and reset timer
			printf("%d - %f ms/frame\n", fps, 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		//

		game.update();
		game.render();
	}

	return 0;
}