#pragma once
#include "../../libs.h"

#include "../shaders/Shader.h"
#include "../camera/Camera.h"
#include "../enviroment/Fog.h"
#include "../entities/lights/LightPoint.h"

class MasterRenderer {
	protected:
		Shader* shader;

	public:
		MasterRenderer(Shader* shader) : shader(shader) { }

		void sendCamera(Camera* camera);
		void sendFog(Fog* fog);
		void sendLightsPoint(std::vector<LightPoint*> lightsPoint);
};