#pragma once
#include <engine/input/MouseInput.h>
#include <engine/WindowUserPointer.h>


MouseInput::MouseInput(std::vector<int> keysToMonitor) : Input(keysToMonitor) { }
MouseInput::~MouseInput() { }

void MouseInput::setKeyCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, callback_button);
	glfwSetScrollCallback(window, callback_wheel);
}

void MouseInput::incWheelX(double xoffset) { this->wheelX += xoffset; }
void MouseInput::incWheelY(double yoffset) { this->wheelY += yoffset; }

double MouseInput::getWheelX() { return wheelX; }
double MouseInput::getWheelY() { return wheelY; }

void MouseInput::resetWheel() { wheelX = 0; wheelY = 0; }

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
