#include "libs.h"
#include "game/Game.h"


// SETTINGS
const unsigned int GL_MAJOR_VER = 4;
const unsigned int GL_MINOR_VER = 4;
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

const float FOV = 90.f;


int main() {
	Game game("Project-CGE", SCR_WIDTH, SCR_HEIGHT, GL_MAJOR_VER, GL_MINOR_VER, true);
	
	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
	}

	return 0;
}