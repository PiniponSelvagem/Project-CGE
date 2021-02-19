#pragma once
#include <engine/input/KeyboardInput.h>
#include <engine/input/MouseInput.h>
#include <engine/camera/Camera.h>

struct WindowUserPointer {
	KeyboardInput* keyboardInput;
	MouseInput* mouseInput;
	Camera* camera;
};
