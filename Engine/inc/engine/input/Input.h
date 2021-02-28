#pragma once
#include <engine/Libs.h>
#include <map>
#include <vector>

class Input {
	protected:
		std::map<int, bool> keys;

		void setKeyState(int key, bool isActive);



	public:
		Input(std::vector<int> keysToMonitor);
		virtual ~Input();

		void addKey(int key);
		void removeKey(int key);


		virtual void setKeyCallback(GLFWwindow* window) = 0;

		bool isKeyActive(int key);
};

