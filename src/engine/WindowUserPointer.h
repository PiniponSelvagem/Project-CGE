#pragma once
#include "input/KeyInput.h"
#include "camera/Camera.h"

struct WindowUserPointer {
	KeyInput* keyInput;
	Camera* camera;
};
