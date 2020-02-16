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

	// TEXTURE 1
	textures.push_back(new Texture("resources/png/grass.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/grass_specular.png", GL_TEXTURE_2D));
}
void Game::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f), 
		0,
		1
	));
}
void Game::initModels() {
	std::vector<Mesh*> meshes;
	std::vector<Mesh*> meshFloor;

	meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	meshFloor.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f, 0.f, -2.f),
			glm::vec3(0.f),
			glm::vec3(-90.f, 0.f, 0.f),
			glm::vec3(20.f)
		)
	);


	models.push_back(new Model(
		glm::vec3(0.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(0.f, 2.f, 2.f),
		materials[MAT_CRATE],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(-2.f, 2.f, 0.f),
		materials[MAT_CRATE],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(0.f, 0.f, 0.f),
		materials[MAT_CRATE],
		textures[TEX_GRASS],
		textures[TEX_GRASS_SPECULAR],
		meshFloor
	));

	/*
	models.push_back(new Model(
		glm::vec3(0.f, 0.f, -20.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		"resources/obj/teapot.obj"
	));
	*/

	for (auto *&i : meshes) {
		delete i;
	}
	for (auto *&i : meshFloor) {
		delete i;
	}
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





	// TODO: this should be in camera class.
	// TODO: this should be in camera class.
	// TODO: this should be in camera class.
	// TODO: this should be in camera class.
	projectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane, farPlane
	);
	/*
	// TODO: axis should be changed so camera does not move like in prespective view, but only along the X and Z axis (maybe Y should be a fixed value???)
	float fov = 10.f;
	float aspectRatioWidth  = ((static_cast<float>(framebufferWidth) / framebufferHeight) / 2.f ) * fov;
	float aspectRatioHeight = 0.5f * fov;
	projectionMatrix = glm::ortho(
		-aspectRatioWidth, aspectRatioWidth,
		-aspectRatioHeight, aspectRatioHeight,
		nearPlane, farPlane
	);
	*/






	shaders[SHADER_CORE_PROGRAM]->setMat4fv(projectionMatrix, "ProjectionMatrix");
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

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.move(dTime, UP);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.move(dTime, DOWN);

	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f, 1.f));
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f,-1.f));
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

	initShaders();
	initTextures();
	initMaterials();
	initModels();
	initLights();
	initUniforms();
}

Game::~Game() {
	glfwDestroyWindow(window);
	glfwTerminate();

	for (size_t i = 0; i < shaders.size();  ++i)  { delete shaders[i];   }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
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

	//models[0]->changeRotation(glm::vec3(0.4f, 0.8f, 1.f));
	models[0]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
	models[1]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
	models[2]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
}

void Game::render() {
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	updateUniforms();
	for (auto *i : models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}

	// END
	glfwSwapBuffers(window);
	glFlush();

	// Reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
