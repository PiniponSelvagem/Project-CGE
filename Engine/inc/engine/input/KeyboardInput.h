#pragma once
#include <engine/Libs.h>
#include <map>
#include <vector>

#include <engine/input/Input.h>

class KeyboardInput : public Input {
	private:
		

	public:
		KeyboardInput(std::vector<int> keysToMonitor);
		~KeyboardInput();

		void setKeyCallback(GLFWwindow* window);

		static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

