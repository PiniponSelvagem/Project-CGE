#include "Func.h"
#include "../../game/Game.h"


Func::Func(std::function<void()> callback) {
	this->callback = callback;
}


Func::~Func() {
}

void Func::run() {
	callback();
}
