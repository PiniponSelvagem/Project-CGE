#pragma once
#include "../../libs.h"
#include "Func.h"

class Input {
	private:
		//Func* func;
		std::function<void()> func;

	public:


		Input(GLFWwindow* window);
		virtual ~Input();

		/*
		void addKeyCallback(int key, Func* func);
		*/
		void addKeyCallback(int key, std::function<void()> func);

		static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};
