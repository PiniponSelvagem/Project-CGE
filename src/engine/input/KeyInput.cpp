#include "KeyInput.h"



KeyInput::KeyInput(std::vector<int> keysToMonitor) {
	for (int i : keysToMonitor) {
		keys[i] = false;
	}
}

KeyInput::~KeyInput() {
}

void KeyInput::addKey(int key) {
	keys.insert(std::map<int, bool>::value_type(key, false));
}
void KeyInput::removeKey(int key) {
	keys.erase(key);
}


void KeyInput::setKeyCallback(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, callback);
}

bool KeyInput::isKeyActive(int key) {
	bool result = false;
	std::map<int, bool>::iterator it = keys.find(key);
	if (it != keys.end()) {
		result = keys[key];
	}
	return result;
}

void KeyInput::setKeyState(int key, bool isActive) {
	std::map<int, bool>::iterator it = keys.find(key);
	if (it != keys.end()) {
		keys[key] = isActive;
	}
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_REPEAT) {
		KeyInput* input = static_cast<KeyInput*>(glfwGetWindowUserPointer(window));
		input->setKeyState(key, action != GLFW_RELEASE);
	}
}
