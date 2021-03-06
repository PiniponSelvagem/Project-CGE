#include "Playground.h"
#include <engine/models/ObjLoader.h>


#define MOUSE_WHEEL_SENSIVITY 1.f
#define MOUSE_SENSIVITY 0.1f

enum texture_enum {
	TEX_DEFAULT, TEX_DEFAULT_SPECULAL,
	TEX_CRATE, TEX_CRATE_SPECULAR,
	TEX_FRAGILE, TEX_FRAGILE_SPECULAR,
	TEX_DGRASS, TEX_DGRASS_SPECULAR,
	TEX_TERRAIN_GRASS,
	TEX_TERRAIN_MUD,
	TEX_TERRAIN_FLOWERS,
	TEX_TERRAIN_PATH,
	TEX_TERRAIN_MUD_SPECULAR,
	TEX_TERRAIN_PATH_SPECULAR
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE,
	MESH_TEAPOT,
	MESH_DGRASS
};

void Playground::initRenderer() {
	// Renderer
	/*
	masterRenderer = new MasterRenderer(
		"resources/shaders/vertex_core.glsl",    "resources/shaders/fragment_core.glsl",	// EntityShader
		"resources/shaders/vertex_terrain.glsl", "resources/shaders/fragment_terrain.glsl"	// TerrainShader
	);
	*/
}
void Playground::initMeshes() {
	meshes.push_back(ObjLoader::loadObj_arrays("resources/obj/cube.obj"));
	meshes.push_back(ObjLoader::loadObj("resources/obj/teapot.obj"));
	meshes.push_back(ObjLoader::loadObj_arrays("resources/obj/digital_grass.obj"));
}
void Playground::initTextures() {
	// TEXTURE - DEFAULT
	textures.push_back(new Texture("resources/png/NO_TEX.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/NO_SPECULAR.png", GL_TEXTURE_2D));

	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));

	// TEXTURE 1
	textures.push_back(new Texture("resources/png/fragile.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/fragile_specular.png", GL_TEXTURE_2D));
	
	// TEXTURE 2
	//textures.push_back(new Texture("resources/png/synthwave_v2.png", GL_TEXTURE_2D));

	// TEXTURE 3
	textures.push_back(new Texture("resources/png/digital_grass.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/digital_grass_spacular.png", GL_TEXTURE_2D));

	//////////////////////////////
	textures.push_back(new Texture("resources/png/terrain_grass.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/terrain_mud.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/terrain_flowers.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/terrain_path.png", GL_TEXTURE_2D));

	textures.push_back(new Texture("resources/png/terrain_mud_specular.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/terrain_path_specular.png", GL_TEXTURE_2D));

	// TERRAIN
	terrainTexPacks.push_back(
		new TerrainTexturePack(
			textures[TEX_TERRAIN_GRASS],	textures[TEX_DEFAULT_SPECULAL],
			textures[TEX_TERRAIN_MUD],		textures[TEX_TERRAIN_MUD_SPECULAR],
			textures[TEX_TERRAIN_FLOWERS],	textures[TEX_DEFAULT_SPECULAL],
			textures[TEX_TERRAIN_PATH],		textures[TEX_TERRAIN_PATH_SPECULAR]
		)
	);
}
void Playground::initMaterials() {
	materials.push_back(new Material(
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(2.f, 0.f, 0.f), //glm::vec3(2.f),
		0,
		1
	));
}
void Playground::initModels() {
	models.push_back(new Model(
		meshes[MESH_CUBE],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		materials[MAT_CRATE]
	));

	models.push_back(new Model(
		meshes[MESH_TEAPOT],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
		materials[MAT_CRATE]
	));
	
	models.push_back(new Model(
		meshes[MESH_DGRASS],
		textures[TEX_DGRASS],
		textures[TEX_DGRASS_SPECULAR],
		materials[MAT_CRATE]
	));

	models.push_back(new Model(
		meshes[MESH_CUBE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		materials[MAT_CRATE]
	));
}
void Playground::initEntities() {
	// TERRAIN
	//terrain = new Terrain(0, 0, "resources/png/heightmap.png", 800.f, 40.f,
	//					  terrainTexPacks[0], new Texture("resources/png/blend_map.png", GL_TEXTURE_2D)
	//);

	player = new Player(
		5.f, 200.f, -50.f, 10.f,
		models[3], glm::vec3(400.f, 0.f, 398.f), glm::vec3(0.f, 0.5f, 0.f), glm::vec3(0.f, 180.f, 0.f)
	);
	entities.push_back(player);

	entities.push_back(new Entity(models[0], glm::vec3(400.f, terrain->getHeight(400.f, 398.f) + 1.f, 398.f), glm::vec3(0.f, 0.5f, 0.f)));	//cube 0
	entities.push_back(new Entity(models[0], glm::vec3(398.f, terrain->getHeight(398.f, 397.f) + 2.f, 397.f), glm::vec3(0.f, 0.5f, 0.f)));	//cube 1
	entities.push_back(new Entity(models[0], glm::vec3(402.f, terrain->getHeight(402.f, 397.f) + 3.f, 397.f), glm::vec3(0.f, 0.5f, 0.f)));	//cube 2
	
	//entities.push_back(new Entity(models[1], glm::vec3(400.f, 0.05f, 400.f)));	//floor
	
	entities.push_back(new Entity(models[1], glm::vec3(400.f, terrain->getHeight(400.f, 360.f), 360.f), glm::vec3(0.f, 7.8f, 0.f)));	//teapot

	// digital grass
	for (int i = 0; i < 400; ++i) {
		float randX = rand() % 40 + 380;
		float randZ = rand() % 40 + 380;
		entities.push_back(new Entity(models[2], glm::vec3(randX, terrain->getHeight(randX, randZ), randZ)));
	}

	/*
	models.push_back(new Model(
		terrain->getMesh(),
		terrain->getTexture(),
		textures[0],
		materials[0]
	));
	*/
}
void Playground::initLights() {
	float intensity = 1.f;

	lightsPoint.push_back(new LightPoint(
		glm::vec3(410.f, 25.f, 410.f), glm::vec3(1.f, 1.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(390.f, 25.f, 390.f), glm::vec3(1.f, 0.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(390.f, 25.f, 410.f), glm::vec3(0.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(410.f, 25.f, 390.f), glm::vec3(0.f, 0.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
}
void Playground::initEnviroment() {
	fog = new Fog(0.003, 5.0);
	ambient = glm::vec3(0.10f);
	//ambient = glm::vec3(0.5f);
}
void Playground::initCamera() {
	camera = new Camera3D_Player3rd(
		player, 1.f, 5.f, 20.f, 180.f, -35.f,
		90.f, 0.001f, 1000.f
	);

	/*
	camera = new Camera3D(
		90.f, 0.001f, 1000.f, glm::vec3(0.f), glm::vec3(0.f)
	);
	*/
}

////////////////////////////////

void Playground::update(float dTime) {
	player->move(dTime, *terrain);
	static_cast<Camera3D_Player3rd*>(camera)->updatePosition();
	//static_cast<Camera2D*>(camera)->updateProjectionMatrix();

	/*
	entities[1]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[2]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[3]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	*/

	//lightSetPosition();
}

void Playground::cameraPanTilt(double mouseOffsetX, double mouseOffsetY) {
	camera->changePanTilt(mouseOffsetX, mouseOffsetY);
}
void Playground::playerFoward()      { player->moveFoward();   }
void Playground::playerBackward()    { player->moveBackward(); }
void Playground::playerLeft()        { player->rotateLeft();   }
void Playground::playerRight()       { player->rotateRight();  }
void Playground::playerJump()        { player->jump();         }

void Playground::cameraZoom(float zoomOffset)  {
	static_cast<Camera3D_Player3rd*>(camera)->changeDistanceFromPlayer(zoomOffset * MOUSE_WHEEL_SENSIVITY);
}
void Playground::cameraPith(float pitchOffset) {
	static_cast<Camera3D_Player3rd*>(camera)->changePitch(pitchOffset * MOUSE_SENSIVITY);
}
void Playground::cameraYaw(float yawOffset)    {
	static_cast<Camera3D_Player3rd*>(camera)->changeAngleAroundPlayer(yawOffset * MOUSE_SENSIVITY);
}
void Playground::cameraSetPlayerDirection(float yawOffset) {
	static_cast<Camera3D_Player3rd*>(camera)->changePlayerDirection(yawOffset * MOUSE_SENSIVITY);
}

void Playground::lightSetPosition() { lightsPoint[0]->setPosition(camera->getPosition()); }



/*
#define SPEED_MULT 1

void Playground::cameraFoward(float dTime)   { camera->moveWalk(dTime*SPEED_MULT, FORWARD);  }
void Playground::cameraBackward(float dTime) { camera->moveWalk(dTime*SPEED_MULT, BACKWARD); }
void Playground::cameraLeft(float dTime)     { camera->moveWalk(dTime*SPEED_MULT, LEFT);     }
void Playground::cameraRight(float dTime)    { camera->moveWalk(dTime*SPEED_MULT, RIGHT);    }
void Playground::cameraUp(float dTime)       { camera->moveWalk(dTime*SPEED_MULT, UP);       }
void Playground::cameraDown(float dTime)     { camera->moveWalk(dTime*SPEED_MULT, DOWN);     }
*/
