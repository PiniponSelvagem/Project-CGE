#pragma once
#include <engine/shaders/Shader.h>
#include <engine/render/MasterRenderer.h>
#include <engine/render/EntityRenderer.h>
#include <engine/models/Texture.h>
#include <engine/models/Material.h>
#include <engine/models/Mesh.h>
#include <engine/models/Model.h>
#include <engine/entities/Entity.h>
#include <engine/entities/player/Player.h>
#include <engine/lights/LightPoint.h>
#include <engine/terrains/Terrain.h>
#include <engine/enviroment/Fog.h>
#include <engine/camera/Camera.h>
#include <engine/camera/Camera2D.h>
#include <engine/camera/Camera3D_Player3rd.h>
#include <engine/ui/UI.h>

class Scene {
	private:
		void loadFromFile();


	protected:
		const char* sceneFile;

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

		// UI Textures
		std::vector<UI*> ui;

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
		virtual void initCamera() = 0;



	public:
		Scene(const char* sceneFile) : sceneFile(sceneFile) { }
		virtual ~Scene();
		void initScene();

		void reloadShader();

		Camera* getMainCamera();

		virtual void update(float dTime) = 0;
		void render();

		virtual void playerFoward() { }
		virtual void playerBackward() { }
		virtual void playerLeft() { }
		virtual void playerRight() { }
		virtual void playerStrafeLeft() { }
		virtual void playerStrafeRight() { }
		virtual void playerJump() { }

		virtual void cameraZoom(float zoomOffset) { }
		virtual void cameraPith(float pitchOffset) { }
		virtual void cameraYaw(float yawOffset) { }
		virtual void cameraSetPlayerDirection(float yawOffset) { }

		/* Useful for free camera */
		virtual void cameraPanTilt(double mouseOffsetX, double mouseOffsetY) { }
		virtual void cameraFoward(float dTime) { }
		virtual void cameraBackward(float dTime) { }
		virtual void cameraLeft(float dTime) { }
		virtual void cameraRight(float dTime) { }
		virtual void cameraUp(float dTime) { }
		virtual void cameraDown(float dTime) { }
		/**************************/

		virtual void lightSetPosition() { }
};

