#pragma once
#include "MouseInput.h"
#include "../WindowUserPointer.h"


MouseInput::MouseInput(std::vector<int> keysToMonitor) : Input(keysToMonitor) {
}

MouseInput::~MouseInput() {
}

void MouseInput::setKeyCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, callback);
}

void MouseInput::callback(GLFWwindow* window, int button, int action, int mods) {
	if (action != GLFW_REPEAT) {
		WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
		wup->mouseInput->setKeyState(button, action != GLFW_RELEASE);
	}
}
