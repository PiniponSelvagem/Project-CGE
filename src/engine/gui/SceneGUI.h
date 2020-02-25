#pragma once
#include "../Shader.h"
#include "../models/Texture.h"
#include "MaterialGUI.h"
#include "../models/Mesh.h"
#include "ModelGUI.h"
#include "CameraGUI.h"

class SceneGUI {
	protected:
		// Camera
		CameraGUI* camera;

		// Shaders
		Shader* shader;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<MaterialGUI*> materials;

		// Models
		std::vector<ModelGUI*> models;


		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initUniforms();

		void updateUniforms();



	public:
		SceneGUI();
		~SceneGUI();
		void initScene();

		CameraGUI* getMainCamera();

		void update();
		void render();
};

