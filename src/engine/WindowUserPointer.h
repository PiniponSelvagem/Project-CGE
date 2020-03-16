#pragma once
#include "input/KeyboardInput.h"
#include "input/MouseInput.h"
#include "camera/Camera.h"
#include "ui/CameraUI.h"

struct WindowUserPointer {
	KeyboardInput* keyboardInput;
	MouseInput* mouseInput;
	Camera* camera;
	CameraUI* cameraUI;
};
