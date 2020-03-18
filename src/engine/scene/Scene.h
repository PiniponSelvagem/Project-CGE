#pragma once
#include "../shaders/Shader.h"
#include "../models/Texture.h"
#include "../models/Material.h"
#include "../models/Mesh.h"
#include "../models/Model.h"
#include "../camera/Camera.h"
#include "../ui/CameraUI.h"
#include "../lights/Light.h"

class Scene {
	protected:
		// Camera
		Camera* camera;

		// Shaders
		std::vector<Shader*> shaders;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<Material*> materials;

		// Models
		std::vector<Model*> models;

		// Lights
		std::vector<LightPoint*> lightsPoint;


		virtual void initShaders() = 0;
		virtual void initTextures() = 0;
		virtual void initMaterials() = 0;
		virtual void initModels() = 0;
		virtual void initLights() = 0;
		void initUniforms();

		void updateUniforms();



	public:
		Scene();
		virtual ~Scene();
		void initScene();

		void reloadShader();

		Camera* getMainCamera();

		virtual void update() = 0;
		void render();

		/* TODO: Make Player class??? */
		virtual void cameraPanTilt(float dTime, double mouseOffsetX, double mouseOffsetY) = 0;
		virtual void cameraFoward(float dTime) = 0;
		virtual void cameraBackward(float dTime) = 0;
		virtual void cameraLeft(float dTime) = 0;
		virtual void cameraRight(float dTime) = 0;
		virtual void cameraUp(float dTime) = 0;
		virtual void cameraDown(float dTime) = 0;

		virtual void lightSetPosition() = 0;
		/******************************/
};

