#pragma once
#include "../Shader.h"
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


		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initUniforms();

		void updateUniforms();



	public:
		SceneUI();
		~SceneUI();
		void initScene();

		CameraUI* getMainCamera();

		void update();
		void render();
};

