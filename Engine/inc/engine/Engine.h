#pragma once
#include <engine/Libs.h>

#include <engine/shaders/Shader.h>
#include <engine/models/Vertex.h>
#include <engine/models/Texture.h>
#include <engine/models/Material.h>
#include <engine/models/Mesh.h>
#include <engine/models/Model.h>
#include <engine/models/ObjLoader.h>
#include <engine/camera/Camera.h>

#include <engine/input/KeyboardInput.h>
#include <engine/input/MouseInput.h>
#include <engine/WindowUserPointer.h>

#include <engine/scene/Scene.h>



class Engine {
	protected:
		// Window
		GLFWwindow* window;
		WindowUserPointer* wuPointer;

		// Delta Time
		float dTime;
		float curTime;
		float lastTime;

		// Input
		KeyboardInput* keyboardInput;
		MouseInput* mouseInput;

		// Mouse Input
		double lastMouseX, lastMouseY;
		double mouseX, mouseY;
		double mouseOffsetX, mouseOffsetY;
		bool firstMouse;

		// Scenes
		Scene* scene;
		
		void initWindow(const char* title, const int width, const int height, bool resizable);
		void initGLFW();
		void initGLAD();	//AFTER CONTEXT CREATION
		void initOpenGLoptions();
		
		void updateDTime();
		virtual void updateMouseInput() = 0;
		virtual void updateKeyboardInput() = 0;

		void updateInput();

		void renderStart();
		void renderEnd();


	public:
		Engine(const char* title, const int width, const int height, bool resizable);
		virtual ~Engine();

		virtual void initInput() = 0;

		inline void setWindowShouldClose() {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		inline int getWindowShouldClose() {
			return glfwWindowShouldClose(window);
		}

		void getWindowSize(float &width, float &height);
		float getWindowAspectRatio();
		
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		virtual void loadScene() = 0;

		void update();
		void render();
};

