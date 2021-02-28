#pragma once
#include <engine/Libs.h>
#include <map>
#include <vector>

#include <engine/input/Input.h>

class MouseInput : public Input {
	private:
		/* 
			for some reason callback_wheel offset values return always 0,
			but incrementing these variables directly it works.
			printing to console the offsets always print 0, while i expected 1 for each turn.
			i dont get it, but the work around is to affect wheelX and wheelY directly.
		*/
		double wheelX = 0, wheelY = 0;


	public:
		MouseInput(std::vector<int> keysToMonitor);
		virtual ~MouseInput();

		void setKeyCallback(GLFWwindow* window);

		void incWheelX(double xoffset);
		void incWheelY(double yoffset);

		double getWheelX();
		double getWheelY();

		void resetWheel();

		static void callback_button(GLFWwindow* window, int button, int action, int mods);
		static void callback_wheel(GLFWwindow* window, double xoffset, double offset);
};

