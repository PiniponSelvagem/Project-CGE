#pragma once
#include "../libs.h"

#include "shaders/Shader.h"
#include "entities/models/Vertex.h"
#include "entities/models/Texture.h"
#include "entities/models/Material.h"
#include "entities/models/primitives/Primitive.h"
#include "entities/models/Mesh.h"
#include "entities/models/Model.h"
#include "entities/models/ObjLoader.h"
#include "camera/Camera.h"

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

