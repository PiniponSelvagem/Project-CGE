#pragma once
#include "input/KeyboardInput.h"
#include "input/MouseInput.h"
#include "camera/Camera.h"

struct WindowUserPointer {
	KeyboardInput* keyboardInput;
	MouseInput* mouseInput;
	Camera* camera;
};
