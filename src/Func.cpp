#include "Func.h"
//#include "../../game/Game.h"


Func::Func(int key, std::function<void()> callback) {
	this->key = key;
	this->callback = callback;
}


Func::~Func() {
}

void Func::run() {
	callback();
}
