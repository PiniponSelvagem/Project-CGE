#pragma once
#include "../shaders/Shader.h"
#include "../render/MasterRenderer.h"
#include "../render/EntityRenderer.h"
#include "../models/Texture.h"
#include "../models/Material.h"
#include "../models/Mesh.h"
#include "../models/Model.h"
#include "../entities/Entity.h"
#include "../entities/player/Player.h"
#include "../lights/LightPoint.h"
#include "../terrains/Terrain.h"
#include "../enviroment/Fog.h"
#include "../camera/Camera.h"

class Scene {
	protected:
		// Camera
		Camera* camera;

		// Renderer
		MasterRenderer* masterRenderer;

		// Meshes
		std::vector<Mesh*> meshes;

		// Textures
		std::vector<Texture*> textures;
		std::vector<TerrainTexturePack*> terrainTexPacks;

		// Materials
		std::vector<Material*> materials;

		// Models
		std::vector<Model*> models;

		// Entities
		std::vector<Entity*> entities;
		Player* player;

		// Terrains
		Terrain* terrain;

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

		virtual void cameraPanTilt(double mouseOffsetX, double mouseOffsetY) = 0;
		virtual void playerFoward() { }
		virtual void playerBackward() { }
		virtual void playerLeft() { }
		virtual void playerRight() { }
		virtual void playerJump() { }
		virtual void cameraDown(float dTime) { }

		virtual void lightSetPosition() { }
};

