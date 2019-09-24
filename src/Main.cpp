#include "libs.h"


// SETTINGS
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;


Vertex vertices[] = {
	//Position							//Color							//Texcoords
	glm::vec3(-0.5f, 0.5f, 0.0f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),
	glm::vec3(-0.5f,-0.5f, 0.0f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),
	glm::vec3( 0.5f,-0.5f, 0.0f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),
	glm::vec3( 0.5f, 0.5f, 0.0f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
	0, 1, 2,	//Tri 1
	0, 2, 3		//Tri 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);



bool loadShader(GLuint &program) {
	bool loadSuccess = true;

	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	// VERTEX
	in_file.open("resources/shaders/vertex_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + "\n";
		}
	}
	else {
		std::cout << "Failed to load vertex file." << std::endl;
		loadSuccess = false;
	}

	in_file.close();

	GLuint vxShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vxShader, 1, &vertSrc, NULL);
	glCompileShader(vxShader);
	glGetShaderiv(vxShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vxShader, 512, NULL, infoLog);
		std::cout << "Failed to compile vertex file." << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	// ----------

	temp = "";
	src = "";

	// FRAGMENT
	in_file.open("resources/shaders/fragment_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + "\n";
		}
	}
	else {
		std::cout << "Failed to load fragment file." << std::endl;
		loadSuccess = false;
	}

	in_file.close();

	GLuint fgShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fgShader, 1, &fragSrc, NULL);
	glCompileShader(fgShader);
	glGetShaderiv(fgShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fgShader, 512, NULL, infoLog);
		std::cout << "Failed to compile fragment file." << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	// PROGRAM
	program = glCreateProgram();
	glAttachShader(program, vxShader);
	glAttachShader(program, fgShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Failed to link program." << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	// END
	glUseProgram(0);
	glDeleteShader(vxShader);
	glDeleteShader(fgShader);

	return loadSuccess;
}




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



void loadTexture(GLuint &texture, const char* fileName) {
	int image_width, image_height;
	unsigned char* image = SOIL_load_image(fileName, &image_width, &image_height, NULL, SOIL_LOAD_RGBA);
	const char* soil_log = SOIL_last_result();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //S -> x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //T -> y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture. " << soil_log << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
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
	GLuint core_program;
	if (!loadShader(core_program)) {
		glfwTerminate();
	}



	// VAO, VBO, EBO
	// - VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// - VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW if changes more often

	// - EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// SET VERTEXATTRIBPOINTERS AND ENABLE
	// -- position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// -- color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// -- texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	// BIND VAO
	glBindVertexArray(0);


	// TEXTURE 0
	GLuint texture0;
	loadTexture(texture0, "resources/png/fragile.png");
	// TEXTURE 1
	GLuint texture1;
	loadTexture(texture1, "resources/png/crate.png");


	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));	//X
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));	//Y
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));	//Z
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));

	glUseProgram(core_program);
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUseProgram(0);


	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		// UPDATE INPUT
		processInput(window);

		// UPDATE


		// CLEAR
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// DRAW
		glUseProgram(core_program);

		// -- update uniforms
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
		glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);

		// MOVE, ROTATE, SCALE
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));	//X
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));	//Y
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));	//Z
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));
		glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));

		// -- activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);


		// END
		glfwSwapBuffers(window);
		glfwPollEvents();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glfwTerminate();
	glDeleteProgram(core_program);

	return 0;
}