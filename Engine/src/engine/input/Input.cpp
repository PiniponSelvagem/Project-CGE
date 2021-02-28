#pragma once
#include <engine/input/Input.h>
#include <engine/WindowUserPointer.h>


void Input::setKeyState(int key, bool isActive) {
	std::map<int, bool>::iterator it = keys.find(key);
	if (it != keys.end()) {
		keys[key] = isActive;
	}
}



Input::Input(std::vector<int> keysToMonitor) {
	for (int i : keysToMonitor) {
		keys[i] = false;
	}
}
Input::~Input() { }

void Input::addKey(int key) {
	keys.insert(std::map<int, bool>::value_type(key, false));
}
void Input::removeKey(int key) {
	keys.erase(key);
}


bool Input::isKeyActive(int key) {
	bool result = false;
	std::map<int, bool>::iterator it = keys.find(key);
	if (it != keys.end()) {
		result = keys[key];
	}
	return result;
}
