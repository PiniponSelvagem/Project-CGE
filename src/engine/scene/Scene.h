#pragma once
#include "../shaders/Shader.h"
#include "../render/MasterRenderer.h"
#include "../render/EntityRenderer.h"
#include "../entities/models/Texture.h"
#include "../entities/models/Material.h"
#include "../entities/models/Mesh.h"
#include "../entities/models/Model.h"
#include "../entities/models/Entity.h"
#include "../entities/lights/LightPoint.h"
#include "../enviroment/Fog.h"
#include "../camera/Camera.h"
#include "../ui/CameraUI.h"

class Scene {
	protected:
		// Camera
		Camera* camera;

		// Shaders
		std::vector<Shader*> shaders;

		// Renderers
		MasterRenderer* masterRenderer;

		// Meshes
		std::vector<Mesh*> meshes;

		// Textures
		std::vector<Texture*> textures;

		// Materials
		std::vector<Material*> materials;

		// Models
		std::vector<Model*> models;

		// Entities
		std::vector<Entity*> entities;

		// Lights
		std::vector<LightPoint*> lightsPoint;

		// Enviroment
		Fog* fog;
		glm::vec3 ambient;


		virtual void initRenderer() = 0;
		virtual void initMeshes() = 0;
		virtual void initTextures() = 0;
		virtual void initMaterials() = 0;
		virtual void initModels() = 0;
		virtual void initEntities() = 0;
		virtual void initLights() = 0;
		virtual void initEnviroment() = 0;



	public:
		Scene();
		virtual ~Scene();
		void initScene();

		void reloadShader();

		Camera* getMainCamera();

		virtual void update(float dTime) = 0;
		void render();

		/* TODO: Make Player class??? */
		virtual void cameraPanTilt(double mouseOffsetX, double mouseOffsetY) = 0;
		virtual void cameraFoward(float dTime) = 0;
		virtual void cameraBackward(float dTime) = 0;
		virtual void cameraLeft(float dTime) = 0;
		virtual void cameraRight(float dTime) = 0;
		virtual void cameraUp(float dTime) = 0;
		virtual void cameraDown(float dTime) = 0;

		virtual void lightSetPosition() = 0;
		/******************************/
};

