#pragma once

#include "../libs.h"

enum shader_enum{
	SHADER_CORE_PROGRAM
};

enum texture_enum {
	TEX_CRATE, TEX_CRATE_SPECULAR,
	TEX_FRAGILE, TEX_FRAGILE_SPECULAR
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE,
	MESH_QUAD
};



class Game {
	private:
		// Window
		GLFWwindow * window;
		const int WINDOW_WIDTH, WINDOW_HEIGHT;
		int framebufferWidth, framebufferHeight;

		// OpenGL Context
		const int GL_MAJOR_VER, GL_MINOR_VER;

		// Delta Time
		float dTime;
		float curTime;
		float lastTime;

		// Mouse Input
		double lastMouseX, lastMouseY;
		double mouseX, mouseY;
		double mouseOffsetX, mouseOffsetY;
		bool firstMouse;

		// Camera
		Camera camera;

		// Matrices
		//glm::mat4 viewMatrix;
		glm::vec3 camPosition;
		//glm::vec3 worldUp;
		//glm::vec3 camFront;

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
		
		// Models
		std::vector<Model*> models;
		
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
		void initModels();
		void initLights();
		void initUniforms();

		void updateUniforms();

		/*
		void updateInput();
		void updateInput(Mesh &mesh);
		*/
		
		void updateDTime();
		void updateMouseInput();
		void updateKeyboardInput();


	public:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		Game(const char* title, const int width, const int height, const int glMajorVer, const int glMinorVer, bool resizable);
		virtual ~Game();

		int getWindowShouldClose();

		void setWindowShouldClose();
		
		void updateInput();

		void update();
		void render();
};
