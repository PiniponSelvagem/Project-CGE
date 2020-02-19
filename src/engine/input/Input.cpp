#pragma once
#include "Input.h"

Input::Input(GLFWwindow* window) {
	glfwSetKeyCallback(window, callback);
}

Input::~Input() {
}

/*
void Input::addKeyCallback(int key, Func* func) {
	this->func = func;
}
*/
void Input::addKeyCallback(int key, std::function<void()> func) {
	this->func = func;
}


void Input::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    
	std::cout << key << " - " << action << std::endl;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //if not pressed == GLFW_RELEASE
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	/*
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Func* func2 = input->func;
		func2->run();
	}
	*/
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		double time = glfwGetTime();
		input->func();
		double time2 = glfwGetTime() - time;
		std::cout << "Input::callback: " << time2 << std::endl;
	}

	/*
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(dTime, FORWARD);
	/*
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(dTime, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(dTime, LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(dTime, RIGHT);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.move(dTime, UP);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.move(dTime, DOWN);

	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f, 1.f));
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		models[0]->changePosition(glm::vec3(0.f, 0.f, -1.f));
	*/

	/*
	// Send key event to all KeyInput instances
	for (Input* input : _instances) {
		input->setIsKeyDown(key, action != GLFW_RELEASE);
	}
	*/
}