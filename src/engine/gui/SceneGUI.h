#pragma once
#include "../Shader.h"
#include "../models/Texture.h"
#include "../models/Material.h"
#include "../models/Mesh.h"
#include "../models/Model.h"
#include "CameraGUI.h"

class SceneGUI {
	protected:
		// Camera
		CameraGUI* camera;

		// Shaders
		std::vector<Shader*> shaders;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<Material*> materials;

		// Models
		std::vector<Model*> models;

		// Lights
		std::vector<glm::vec3*> lights;


		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();
		void initLights();
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

