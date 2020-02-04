#include "libs.h"


// SETTINGS
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

const float FOV = 90.f;


Vertex vertices[] = {
	//Position							//Color							//Texcoords					//Normals				
	glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3( 0.5f,-0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3( 0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

	glm::vec3( 0.5f, 0.5f,-0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, -1.f),
	glm::vec3( 0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
	glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
	0, 1, 2,	//Tri 1
	0, 2, 3,	//Tri 2

	7, 6, 1,
	7, 1, 0,
	
	1, 6, 5,
	1, 2, 5,
	
	3, 2, 4,
	4, 2, 5,
	
	7, 0, 3,
	7, 3, 4,
	
	4, 5, 7,
	5, 6, 7
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);




void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void updateInput(GLFWwindow* window, Mesh &mesh) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.changePosition(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(-0.1f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		mesh.changeRotation(glm::vec3(0.1f));
	}
}


int main() {
	// INIT GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// CREATE WINDOW
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project-CGE", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// INIT GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	// INIT SHADER
	Shader core_program("resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl");


	// MODEL MESH
	Mesh mesh1(vertices, nrOfVertices, indices, nrOfIndices);


	// TEXTURE 0
	Texture texture0("resources/png/crate.png", GL_TEXTURE_2D, 0);
	// TEXTURE 1
	Texture texture1("resources/png/fragile.png", GL_TEXTURE_2D, 1);

	// MATERIAL 0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture1.getTextureUnit());

	// INIT MATRIX
	glm::vec3 cameraPos(0.f, 0.f, 1.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(cameraPos, cameraPos + camFront, worldUp);

	float nearPane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(
		glm::radians(FOV),
		static_cast<float>(SCR_WIDTH) / SCR_HEIGHT,	//static_cast<float>(framebufferWidth) / frameBufferHeight,
		nearPane,
		farPlane
	);

	// LIGHT
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	// INIT UNIFORMS
	core_program.use();

	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(cameraPos, "cameraPos");

	core_program.unuse();

	int i = 0;
	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		// UPDATE INPUT
		glfwPollEvents();

		// UPDATE
		updateInput(window, mesh1);
		processInput(window);


		// CLEAR
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// -- update uniforms
		core_program.set1i(texture0.getTextureUnit(), "texture0");
		core_program.set1i(texture1.getTextureUnit(), "texture1");
		material0.sendToShader(core_program);
		

		//TODO:
		//* move this below to a place where only when window is resized
		//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
		ProjectionMatrix = glm::perspective(
			glm::radians(FOV),
			static_cast<float>(SCR_WIDTH) / SCR_HEIGHT,	//static_cast<float>(framebufferWidth) / frameBufferHeight,
			nearPane,
			farPlane
		);
		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		//*/

		// DRAW
		core_program.use();

		// -- activate texture
		texture0.bind();
		//texture1.bind();

		mesh1.render(&core_program);
		mesh2.render(&core_program);

		// END
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D, 1);
	}

	glfwTerminate();

	return 0;
}