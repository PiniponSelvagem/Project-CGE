#pragma once
#include "KeyboardInput.h"
#include "../WindowUserPointer.h"


KeyboardInput::KeyboardInput(std::vector<int> keysToMonitor) : Input(keysToMonitor) {
}

KeyboardInput::~KeyboardInput() {
}

void KeyboardInput::setKeyCallback(GLFWwindow* window) {
	glfwSetKeyCallback(window, callback);
}

void KeyboardInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_REPEAT) {
		WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
		wup->keyboardInput->setKeyState(key, action != GLFW_RELEASE);
	}
}
