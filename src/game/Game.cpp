#pragma once
#include "Game.h"
#include "scene/Playground.h"
#include "ui/TestUI.h"


void Game::updateMouseInput() {
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (firstMouse) {
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		firstMouse = false;
	}

	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = lastMouseY - mouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	scene->cameraPanTilt(dTime, mouseOffsetX, mouseOffsetY);
}
void Game::updateKeyboardInput() {
	if (keyboardInput->isKeyActive(GLFW_KEY_ESCAPE)) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (keyboardInput->isKeyActive(GLFW_KEY_M))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (keyboardInput->isKeyActive(GLFW_KEY_N))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (keyboardInput->isKeyActive(GLFW_KEY_R))
		scene->reloadShader();
	if (keyboardInput->isKeyActive(GLFW_KEY_E)) {
		loadScene();
		loadSceneUI();
	}

	if (keyboardInput->isKeyActive(GLFW_KEY_0))
		glfwSwapInterval(0);
	if (keyboardInput->isKeyActive(GLFW_KEY_9))
		glfwSwapInterval(1);

	if (keyboardInput->isKeyActive(GLFW_KEY_W))
		scene->cameraFoward(dTime);
	if (keyboardInput->isKeyActive(GLFW_KEY_S))
		scene->cameraBackward(dTime);
	if (keyboardInput->isKeyActive(GLFW_KEY_A))
		scene->cameraLeft(dTime);
	if (keyboardInput->isKeyActive(GLFW_KEY_D))
		scene->cameraRight(dTime);

	if (keyboardInput->isKeyActive(GLFW_KEY_SPACE))
		scene->cameraUp(dTime);
	if (keyboardInput->isKeyActive(GLFW_KEY_LEFT_CONTROL))
		scene->cameraDown(dTime);


	if (mouseInput->isKeyActive(GLFW_MOUSE_BUTTON_1))
		scene->lightSetPosition();
}


////////////////////////////////


Game::Game(const char* title, const int width, const int height, bool resizable)
: Engine(title, width, height, resizable) {
}
Game::~Game() {
}

void Game::initInput() {
	// Keyboard Input
	std::vector<int> keys;
	keys.push_back(GLFW_KEY_ESCAPE);

	keys.push_back(GLFW_KEY_M);
	keys.push_back(GLFW_KEY_N);

	keys.push_back(GLFW_KEY_R);
	keys.push_back(GLFW_KEY_E);

	keys.push_back(GLFW_KEY_0);
	keys.push_back(GLFW_KEY_9);

	keys.push_back(GLFW_KEY_W);
	keys.push_back(GLFW_KEY_S);
	keys.push_back(GLFW_KEY_A);
	keys.push_back(GLFW_KEY_D);
	keys.push_back(GLFW_KEY_SPACE);
	keys.push_back(GLFW_KEY_LEFT_CONTROL);

	keys.push_back(GLFW_KEY_PAGE_UP);
	keys.push_back(GLFW_KEY_PAGE_DOWN);
	keyboardInput = new KeyboardInput(keys);
	keyboardInput->setKeyCallback(window);
	wuPointer->keyboardInput = keyboardInput;


	// Mouse Input
	std::vector<int> buttons;
	buttons.push_back(GLFW_MOUSE_BUTTON_1);

	mouseInput = new MouseInput(buttons);
	mouseInput->setKeyCallback(window);
	wuPointer->mouseInput = mouseInput;
}

void Game::loadScene() {
	delete scene;
	scene = new Playground();
	scene->initScene();
	wuPointer->camera = scene->getMainCamera();
}
void Game::loadSceneUI() {
	delete sceneUI;
	sceneUI = new TestUI();
	sceneUI->initScene();
	wuPointer->cameraUI = sceneUI->getMainCamera();
}