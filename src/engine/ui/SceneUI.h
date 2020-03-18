#pragma once
#include "../shaders/Shader.h"
#include "../models/Texture.h"
#include "MaterialUI.h"
#include "../models/Mesh.h"
#include "ModelUI.h"
#include "CameraUI.h"

class SceneUI {
	protected:
		// Camera
		CameraUI* camera;

		// Shaders
		Shader* shader;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<MaterialUI*> materials;

		// Models
		std::vector<ModelUI*> models;


		virtual void initShaders() = 0;
		virtual void initTextures() = 0;
		virtual void initMaterials() = 0;
		virtual void initModels() = 0;
		void initUniforms();

		void updateUniforms();


	public:
		SceneUI();
		virtual ~SceneUI();

		void initScene();

		CameraUI* getMainCamera();

		virtual void update() = 0;
		void render();
};

