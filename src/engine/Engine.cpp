#pragma once
#include "Engine.h"

void Engine::initWindow(const char * title, const int width, int height, bool resizable) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// CREATE WINDOW
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "ERROR::GAME::GLFW_CREATE_WINDOW" << std::endl;
		glfwTerminate();
		//TODO: return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);

	glfwSetWindowUserPointer(window, this);
}
void Engine::initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "ERROR::GAME::GLFW_INIT" << std::endl;
		glfwTerminate();
		//TODO: return -1;
	}
}
void Engine::initGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::GAME::GLAD_INIT" << std::endl;
		//TODO: return -1;
	}
}
void Engine::initOpenGLoptions() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Engine::updateDTime() {
	curTime = static_cast<float>(glfwGetTime());
	dTime = curTime - lastTime;
	lastTime = curTime;
}

void Engine::updateInput() {
	glfwPollEvents();
	updateMouseInput();
	updateKeyboardInput();
}

void Engine::renderStart() {
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Engine::renderEnd() {
	// END
	glfwSwapBuffers(window);
	glFlush();

	// RESET
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


////////////////////////////////


Engine::Engine(const char* title, const int width, const int height, bool resizable) {
	dTime = 0.f;
	curTime = 0.f;
	lastTime = 0.f;

	lastMouseX = 0.f;
	lastMouseY = 0.f;
	mouseX = 0.f;
	mouseY = 0.f;
	mouseOffsetX = 0.f;
	mouseOffsetY = 0.f;
	firstMouse = true;

	initGLFW();
	initWindow(title, width, height, resizable);
	initGLAD();
	initOpenGLoptions();

	wuPointer = new WindowUserPointer();
	glfwSetWindowUserPointer(window, wuPointer);

	//TODO: framebuffer_size_callback(window, width, height);
}

Engine::~Engine() {
	glfwDestroyWindow(window);
	glfwTerminate();
	delete scene;
	delete sceneUI;
	delete keyboardInput;
	delete mouseInput;
	delete wuPointer;
}

void Engine::getWindowSize(float &width, float &height) {
	int int_width, int_height;
	glfwGetWindowSize(window, &int_width, &int_height);
	width = int_width;
	height = int_height;
}

float Engine::getWindowAspectRatio() {
	float width, height;
	getWindowSize(width, height);
	if (width == 0)  width = 1;
	if (height == 0) height = 1;

	return width / height;
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	
	if (fbWidth == 0)  fbWidth = 1;
	if (fbHeight == 0) fbHeight = 1;

	if (wup->camera != nullptr) {
		wup->camera->setAspectRatio(static_cast<float>(fbWidth) / fbHeight);
	}
	if (wup->cameraUI != nullptr) {
		wup->cameraUI->setUIWindowSize(static_cast<float>(fbWidth), static_cast<float>(fbHeight));
	}
	glViewport(0, 0, width, height);
}

void Engine::update() {
	updateDTime();
	updateInput();

	scene->update(dTime);
	sceneUI->update();
}
void Engine::render() {
	renderStart();

	scene->render();
	sceneUI->render();

	renderEnd();
}
