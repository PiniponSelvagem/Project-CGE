#include "Game.h"


void Game::initWindow(const char * title, bool resizable) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_MAJOR_VER);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_MINOR_VER);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	// CREATE WINDOW
	this-> window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == NULL) {
		std::cout << "ERROR::GAME::GLFW_CREATE_WINDOW" << std::endl;
		glfwTerminate();
		//TODO: return -1;
	}
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_size_callback);
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

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Game::initMatrices() {
	this->viewMatrix = glm::mat4(1.f);
	this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	//this->projectionMatrix = glm::mat4(1.f);
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		nearPlane,
		farPlane
	);
}

void Game::initShaders() {
	this->shaders.push_back(new Shader(this->GL_MAJOR_VER, this->GL_MINOR_VER, "resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));
}
void Game::initTextures() {
	// TEXTURE 0
	this->textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));

	// TEXTURE 1
	this->textures.push_back(new Texture("resources/png/fragile.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("resources/png/fragile_specular.png", GL_TEXTURE_2D));
}
void Game::initMaterials() {
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 
		TEX_CRATE,
		TEX_CRATE_SPECULAR
	));
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		TEX_FRAGILE,
		TEX_FRAGILE_SPECULAR
	));
}
void Game::initMeshes() {
	this->meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
	this->meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
}
void Game::initLights() {
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}
void Game::initUniforms() {
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::updateUniforms() {
	// Update viewMatrix (camera)
	this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");

	// Update frameBuffer size and projectionMatrix
	//TODO: maybe only do this when window size changes?
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
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
	this->curTime = static_cast<float>(glfwGetTime());
	this->dTime = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}
void Game::updateMouseInput() {
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (firstMouse) {
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		firstMouse = false;
	}

	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;
}
void Game::updateKeyboardInput() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);

	if (glfwGetKey(this->window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(this->window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		this->camPosition.z -= 0.05f;
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		this->camPosition.z += 0.05f;
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		this->camPosition.x -= 0.05f;
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		this->camPosition.x += 0.05f;

	if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		this->camPosition.y -= 0.05f;
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->camPosition.y += 0.05f;
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}

Game::Game(const char* title, const int width, const int height, const int glMajorVer, const int glMinorVer, bool resizable) 
: WINDOW_WIDTH(width), WINDOW_HEIGHT(height), GL_MAJOR_VER(glMajorVer), GL_MINOR_VER(glMinorVer) {
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;
	
	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	this->projectionMatrix = glm::mat4(1.f);

	this->dTime = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.f;
	this->lastMouseY = 0.f;
	this->mouseX = 0.f;
	this->mouseY = 0.f;
	this->mouseOffsetX = 0.f;
	this->mouseOffsetY = 0.f;
	this->firstMouse = true;
	
	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLAD();
	this->initOpenGLoptions();
	this->initMatrices();

	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();
}

Game::~Game() {
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size();  ++i)  { delete this->shaders[i];   }
	for (size_t i = 0; i < this->textures.size(); ++i)  { delete this->textures[i];  }
	for (size_t i = 0; i < this->materials.size(); ++i) { delete this->materials[i]; }
	for (size_t i = 0; i < this->meshes.size(); ++i)    { delete this->meshes[i];    }
	for (size_t i = 0; i < this->lights.size(); ++i)    { delete this->lights[i];    }
}

void Game::setWindowShouldClose() {
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

int Game::getWindowShouldClose() {
	return glfwWindowShouldClose(this->window);
}

void Game::updateInput() {
	glfwPollEvents();
	this->updateMouseInput();
	this->updateKeyboardInput();
}

void Game::update() {
	// UPDATE INPUT
	//updateInput(*this->meshes[MESH_CUBE]);
	updateDTime();
	updateInput();

	std::cout
		<< "DT: " << dTime << std::endl
		<< "Mouse offset X: " << mouseOffsetX << std::endl
		<< "Mouse offset Y: " << mouseOffsetY << std::endl;
}

void Game::render() {
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();
	this->materials[MAT_CRATE]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	this->shaders[SHADER_CORE_PROGRAM]->use();

	// -- activate texture
	this->textures[TEX_CRATE]->bind(0);
	this->textures[TEX_CRATE_SPECULAR]->bind(1);

	// DRAW
	this->meshes[MESH_CUBE]->render(this->shaders[SHADER_CORE_PROGRAM]);

	// END
	glfwSwapBuffers(window);
	glFlush();

	// Reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
