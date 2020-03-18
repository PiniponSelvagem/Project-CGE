#pragma once
#include "../libs.h"

#include "models/Vertex.h"
#include "shaders/Shader.h"
#include "models/Texture.h"
#include "models/Material.h"
#include "models/primitives/Primitive.h"
#include "models/Mesh.h"
#include "models/Model.h"
#include "camera/Camera.h"
#include "models/ObjLoader.h"

#include "input/KeyboardInput.h"
#include "input/MouseInput.h"
#include "WindowUserPointer.h"

#include "scene/Scene.h"
#include "ui/SceneUI.h"



class Engine {
	protected:
		// Window
		GLFWwindow* window;
		const int WINDOW_WIDTH, WINDOW_HEIGHT;
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
		SceneUI* sceneUI;
		
		void initWindow(const char * title, bool resizable);
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

		int getWindowShouldClose();
		void setWindowShouldClose();
		
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		virtual void loadScene() = 0;
		virtual void loadSceneUI() = 0;

		void update();
		void render();
};

