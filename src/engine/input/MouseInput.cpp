#pragma once
#include "MouseInput.h"
#include "../WindowUserPointer.h"

void MouseInput::setKeyCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, callback_button);
	glfwSetScrollCallback(window, callback_wheel);
}

void MouseInput::callback_button(GLFWwindow* window, int button, int action, int mods) {
	if (action != GLFW_REPEAT) {
		WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
		wup->mouseInput->setKeyState(button, action != GLFW_RELEASE);
	}

	//std::cout << "BUTTON: " << button << " - ACTION: " << action << " - MODS: " << mods << std::endl;
}

void MouseInput::callback_wheel(GLFWwindow* window, double xoffset, double yoffset) {
	WindowUserPointer* wup = static_cast<WindowUserPointer*>(glfwGetWindowUserPointer(window));
	wup->mouseInput->incWheelX(xoffset);
	wup->mouseInput->incWheelY(yoffset);

	/*
	std::cout
		<< "XOFFSET: " << xoffset
		<< " - YOFFSET: " << yoffset
		<< " - wheelX: " << wup->mouseInput->getWheelX()
		<< " - wheelY: " << wup->mouseInput->getWheelY()
		<< std::endl;
	*/
}
