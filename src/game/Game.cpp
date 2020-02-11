#include "Game.h"


void Game::initWindow(const char * title, bool resizable) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_MAJOR_VER);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_MINOR_VER);
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
void Game::initMatrices() {
	/*
	viewMatrix = glm::mat4(1.f);
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	//this->projectionMatrix = glm::mat4(1.f);
	projectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);
	*/
}

void Game::initShaders() {
	shaders.push_back(new Shader(GL_MAJOR_VER, GL_MINOR_VER, "resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));
}
void Game::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));

	// TEXTURE 1
	textures.push_back(new Texture("resources/png/fragile.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/fragile_specular.png", GL_TEXTURE_2D));
}
void Game::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 
		TEX_CRATE,
		TEX_CRATE_SPECULAR
	));
	materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		TEX_FRAGILE,
		TEX_FRAGILE_SPECULAR
	));
}
void Game::initMeshes() {
	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
	meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
}
void Game::initLights() {
	lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}
void Game::initUniforms() {
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(projectionMatrix, "ProjectionMatrix");

	shaders[SHADER_CORE_PROGRAM]->setVec3f(*lights[0], "lightPos0");
}

void Game::updateUniforms() {
	// Update viewMatrix (camera)
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(camera.getPosition(), "cameraPos");

	// Update frameBuffer size and projectionMatrix
	//TODO: maybe only do this when window size changes?
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	projectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(projectionMatrix, "ProjectionMatrix");
}

/*
void Game::updateInput() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);

	if (glfwGetKey(this->window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(this->window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
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
//TODO: improve INPUT handling. Suggestion: https://gamedev.stackexchange.com/questions/150157/how-to-improve-my-input-handling-in-glfw
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
void Game::updateKeyboardInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(dTime, FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(dTime, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(dTime, LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(dTime, RIGHT);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camPosition.y -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camPosition.y += 0.05f;
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}

Game::Game(const char* title, const int width, const int height, const int glMajorVer, const int glMinorVer, bool resizable) 
: WINDOW_WIDTH(width), WINDOW_HEIGHT(height), GL_MAJOR_VER(glMajorVer), GL_MINOR_VER(glMinorVer),
camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)) {

	framebufferWidth  = WINDOW_WIDTH;
	framebufferHeight = WINDOW_HEIGHT;
	
	camPosition = glm::vec3(0.f, 0.f, 1.f);
	//worldUp = glm::vec3(0.f, 1.f, 0.f);
	//camFront = glm::vec3(0.f, 0.f, -1.f);

	fov = 90.f;
	nearPlane = 0.1f;
	farPlane = 1000.f;
	projectionMatrix = glm::mat4(1.f);

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
	initMatrices();

	initShaders();
	initTextures();
	initMaterials();
	initMeshes();
	initLights();
	initUniforms();

	meshes[MESH_CUBE]->setPosition(glm::vec3(0.f, 0.f, -1.f));
}

Game::~Game() {
	glfwDestroyWindow(window);
	glfwTerminate();

	for (size_t i = 0; i < shaders.size();  ++i)  { delete shaders[i];   }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (size_t i = 0; i < meshes.size(); ++i)    { delete meshes[i];    }
	for (size_t i = 0; i < lights.size(); ++i)    { delete lights[i];    }
}

void Game::setWindowShouldClose() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Game::getWindowShouldClose() {
	return glfwWindowShouldClose(window);
}

void Game::updateInput() {
	glfwPollEvents();
	updateMouseInput();
	updateKeyboardInput();
	camera.updateInput(dTime, -1, mouseOffsetX, mouseOffsetY);
}

void Game::update() {
	// UPDATE INPUT
	//updateInput(*this->meshes[MESH_CUBE]);
	updateDTime();
	updateInput();

	meshes[MESH_CUBE]->changeRotation(glm::vec3(0.4f, 0.8f, 1.f));
}

void Game::render() {
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	updateUniforms();
	materials[MAT_CRATE]->sendToShader(*shaders[SHADER_CORE_PROGRAM]);

	shaders[SHADER_CORE_PROGRAM]->use();

	// -- activate texture
	textures[TEX_CRATE]->bind(0);
	textures[TEX_CRATE_SPECULAR]->bind(1);

	// DRAW
	meshes[MESH_CUBE]->render(shaders[SHADER_CORE_PROGRAM]);

	// END
	glfwSwapBuffers(window);
	glFlush();

	// Reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
