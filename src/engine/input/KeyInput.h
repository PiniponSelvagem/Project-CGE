#pragma once
#include "../../libs.h"
#include <map>
#include <vector>

class KeyInput {
	private:
		std::map<int, bool> keys;
		
		void setKeyState(int key, bool isActive);
		


	public:
		KeyInput(std::vector<int> keysToMonitor);
		~KeyInput();

		void addKey(int key);
		void removeKey(int key);


		void setKeyCallback(GLFWwindow* window);
		
		bool isKeyActive(int key);

		static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

