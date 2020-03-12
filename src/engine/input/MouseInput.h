#pragma once
#include "../../libs.h"
#include <map>
#include <vector>

#include "Input.h"

class MouseInput : public Input {
	private:


	public:
		MouseInput(std::vector<int> keysToMonitor);
		~MouseInput();

		void setKeyCallback(GLFWwindow* window);

		static void callback(GLFWwindow* window, int button, int action, int mods);
};

