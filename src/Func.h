#pragma once

#include <functional>

class Func {
	private:
		int key;
		//void(Game::*func)();
		//void(*func)();
		std::function<void()> callback;

	public:
		Func(int key, std::function<void()> callback);
		~Func();

		void run();
};

