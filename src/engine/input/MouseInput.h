#pragma once
#include "../../libs.h"
#include <map>
#include <vector>

#include "Input.h"

class MouseInput : public Input {
	private:
		/* 
			for some reason callback_wheel offset values return always 0,
			but incrementing these variables directly it works.
			printing to console the offsets always print 0, while i expected 1 for each turn
			i dont get it, but the work around is to affect wheelX and wheelY directly.
		*/
		double wheelX = 0, wheelY = 0;


	public:
		MouseInput(std::vector<int> keysToMonitor) : Input(keysToMonitor) { }
		virtual ~MouseInput() { }

		void setKeyCallback(GLFWwindow* window);

		inline void incWheelX(double xoffset) { this->wheelX += xoffset; }
		inline void incWheelY(double yoffset) { this->wheelY += yoffset; }

		inline double getWheelX() { return wheelX; }
		inline double getWheelY() { return wheelY; }

		inline void resetWheel() { wheelX = 0; wheelY = 0; }

		static void callback_button(GLFWwindow* window, int button, int action, int mods);
		static void callback_wheel(GLFWwindow* window, double xoffset, double offset);
};

