#include "Game.h"


void Game::initWindow(const char * title, bool resizable) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// CREATE WINDOW
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "ERROR::GAME::GLFW_CREATE_WINDOW" << std::endl;
		glfwTerminate();
		//TODO: return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Game::framebuffer_size_callback);

	glfwSetWindowUserPointer(window, this);
}
void Game::initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "ERROR::GAME::GLFW_INIT" << std::endl;
		glfwTerminate();
		//TODO: return -1;
	}
}
void Game::initGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::GAME::GLAD_INIT" << std::endl;
		//TODO: return -1;
	}
}
void Game::initOpenGLoptions() {
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

void Game::initInput() {
	// Keyboard Input
	std::vector<int> keys;
	keys.push_back(GLFW_KEY_ESCAPE);

	keys.push_back(GLFW_KEY_M);
	keys.push_back(GLFW_KEY_N);

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

/*
void Game::updateInput(Mesh &mesh) {
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, 0.01f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, -0.01f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS) {
		mesh.changeScale(glm::vec3(-0.1f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_X) == GLFW_PRESS) {
		mesh.changeScale(glm::vec3(0.1f));
	}
}
*/

void Game::updateDTime() {
	curTime = static_cast<float>(glfwGetTime());
	dTime = curTime - lastTime;
	lastTime = curTime;
}

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
}

/*
void Game::updateKeyboardInput() {
	double time = glfwGetTime();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		double time = glfwGetTime();
		camera.move(dTime, FORWARD);
		double time2 = glfwGetTime() - time;
		std::cout << "updateKeyboardInput: " << time2 << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(dTime, FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(dTime, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(dTime, LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(dTime, RIGHT);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.move(dTime, UP);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.move(dTime, DOWN);

	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f, 1.f));
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f, -1.f));

	double time2 = glfwGetTime() - time;
	std::cout << "updateKeyboardInput: " << time2 << std::endl;
}
*/
void Game::updateKeyboardInput() {
	if (keyboardInput->isKeyActive(GLFW_KEY_ESCAPE)) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (keyboardInput->isKeyActive(GLFW_KEY_M))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (keyboardInput->isKeyActive(GLFW_KEY_N))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
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

void Game::updateInput() {
	glfwPollEvents();
	updateMouseInput();
	scene->cameraPanTilt(dTime, mouseOffsetX, mouseOffsetY);
	updateKeyboardInput();
}



void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	if (wup->camera != nullptr) {
		wup->camera->setAspectRatio(static_cast<float>(fbWidth) / fbHeight);
	}
	glViewport(0, 0, width, height);
}

Game::Game(const char* title, const int width, const int height, bool resizable) 
: WINDOW_WIDTH(width), WINDOW_HEIGHT(height) {
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
	initWindow(title, resizable);
	initGLAD();
	initOpenGLoptions();
	
	wuPointer = new WindowUserPointer();
	glfwSetWindowUserPointer(window, wuPointer);

	initInput();

	scene = new Playground();
	scene->initScene();
	wuPointer->camera = scene->getMainCamera();

	sceneGUI = new SceneGUI();
	sceneGUI->initScene();

	framebuffer_size_callback(window, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Game::~Game() {
	glfwDestroyWindow(window);
	glfwTerminate();
	delete scene;
	delete keyboardInput;
	delete mouseInput;
	delete wuPointer;
}

void Game::setWindowShouldClose() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Game::getWindowShouldClose() {
	return glfwWindowShouldClose(window);
}


void Game::update() {
	// UPDATE INPUT
	//updateInput(*this->meshes[MESH_CUBE]);
	updateDTime();
	updateInput();

	scene->update();
	sceneGUI->update();
}

void Game::render() {
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	scene->render();
	sceneGUI->render();
	
	// END
	glfwSwapBuffers(window);
	glFlush();

	// Reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
