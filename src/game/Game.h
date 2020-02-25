#pragma once
#include "../libs.h"

#include "../engine/models/Vertex.h"
#include "../engine/Shader.h"
#include "../engine/models/Texture.h"
#include "../engine/models/Material.h"
#include "../engine/models/primitives/Primitive.h"
#include "../engine/models/Mesh.h"
#include "../engine/models/Model.h"
#include "../engine/camera/Camera.h"
#include "../engine/models/ObjLoader.h"

#include "../engine/input/KeyInput.h"
#include "../engine/WindowUserPointer.h"

#include "scene/Playground.h"

#include "../engine/gui/SceneGUI.h"



class Game {
	private:
		// Window
		GLFWwindow* window;
		const int WINDOW_WIDTH, WINDOW_HEIGHT;
		WindowUserPointer* wuPointer;

		// Delta Time
		float dTime;
		float curTime;
		float lastTime;

		// Keyboard Input
		KeyInput* keyInput;

		// Scenes
		Playground* scene;
		SceneGUI* sceneGUI;

		// Mouse Input
		double lastMouseX, lastMouseY;
		double mouseX, mouseY;
		double mouseOffsetX, mouseOffsetY;
		bool firstMouse;
				
		void initWindow(const char * title, bool resizable);
		void initGLFW();
		void initGLAD();	//AFTER CONTEXT CREATION
		void initOpenGLoptions();

		void initKeyInput();
		
		void updateDTime();
		void updateMouseInput();
		void updateKeyboardInput();

		void updateInput();

	public:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		Game(const char* title, const int width, const int height, bool resizable);
		virtual ~Game();

		int getWindowShouldClose();
		void setWindowShouldClose();
		
		void update();
		void render();
};

