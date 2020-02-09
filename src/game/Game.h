#pragma once

#include "../libs.h"

enum shader_enum{
	SHADER_CORE_PROGRAM = 0
};

enum texture_enum {
	TEX_CRATE_0 = 0,
	TEX_FRAGILE_1 = 1
};

enum material_enum {
	MAT_0 = 0
};

enum mesh_enum {
	MESH_QUAD = 0
};



class Game {
	private:
		// Window
		GLFWwindow * window;
		const int WINDOW_WIDTH, WINDOW_HEIGHT;

		// OpenGL Context
		const int GL_MAJOR_VER, GL_MINOR_VER;

		// Matrices
		glm::mat4 viewMatrix;
		glm::vec3 camPosition;
		glm::vec3 worldUp;
		glm::vec3 camFront;

		glm::mat4 projectionMatrix;
		float fov;
		float nearPlane;
		float farPlane;

		// Shaders
		std::vector<Shader*> shaders;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<Material*> materials;

		// Meshes
		std::vector<Mesh*> meshes;
		
		// Lights
		std::vector<glm::vec3*> lights;

		
		void initWindow(const char * title, bool resizable);
		void initGLFW();
		void initGLAD();	//AFTER CONTEXT CREATION
		void initOpenGLoptions();
		void initMatrices();

		void initShaders();
		void initTextures();
		void initMaterials();
		void initMeshes();
		void initLights();
		void initUniforms();

		void updateUniforms();

		void updateInput();
		void updateInput(Mesh &mesh);


	public:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		Game(const char* title, const int width, const int height, const int glMajorVer, const int glMinorVer, bool resizable);
		virtual ~Game();

		int getWindowShouldClose();

		void setWindowShouldClose();
		
		void update();
		void render();
};

