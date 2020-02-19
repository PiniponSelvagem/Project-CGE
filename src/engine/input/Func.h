#pragma once

#include <functional>

class Func {
	private:
		//void(Game::*func)();
		//void(*func)();
		std::function<void()> callback;

	public:
		Func(std::function<void()> callback);
		~Func();

		void run();
};

