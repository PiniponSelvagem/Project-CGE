#include "Playground.h"
#include "../../engine/entities/models/ObjLoader.h"

#define SPEED_MULT 1

enum texture_enum {
	TEX_DEFAULT,
	TEX_CRATE, TEX_CRATE_SPECULAR,
	TEX_FRAGILE, TEX_FRAGILE_SPECULAR,
	//TEX_GRASS, TEX_GRASS_SPECULAR,
	//TEX_STALL, TEX_STALL_SPECULAR,
	TEX_TERRAIN,
	TEX_DGRASS, TEX_DGRASS_SPECULAR
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE,
	MESH_FLOOR,
	MESH_TEAPOT,
	MESH_DGRASS
};

void Playground::initRenderer() {
	// Renderer
	masterRenderer = new MasterRenderer(
		"resources/shaders/vertex_core.glsl",    "resources/shaders/fragment_core.glsl",	// EntityShader
		"resources/shaders/vertex_terrain.glsl", "resources/shaders/fragment_terrain.glsl"	// TerrainShader
	);
}
void Playground::initMeshes() {
	meshes.push_back(ObjLoader::loadObj_arrays("resources/obj/cube.obj"));
	meshes.push_back(ObjLoader::loadObj("resources/obj/floor.obj"));
	meshes.push_back(ObjLoader::loadObj("resources/obj/teapot.obj"));
	meshes.push_back(ObjLoader::loadObj_arrays("resources/obj/digital_grass.obj"));
}
void Playground::initTextures() {
	// TEXTURE - DEFAULT
	textures.push_back(new Texture("resources/png/NO_TEX.png", GL_TEXTURE_2D));

	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));

	// TEXTURE 1
	textures.push_back(new Texture("resources/png/fragile.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/fragile_specular.png", GL_TEXTURE_2D));
	
	// TEXTURE 2
	textures.push_back(new Texture("resources/png/synthwave_v2.png", GL_TEXTURE_2D));

	// TEXTURE 3
	textures.push_back(new Texture("resources/png/digital_grass.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/digital_grass_spacular.png", GL_TEXTURE_2D));
}
void Playground::initMaterials() {
	materials.push_back(new Material(
		glm::vec3(1.f),
		glm::vec3(2.f),
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
		meshes[MESH_FLOOR],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
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
}
void Playground::initEntities() {
	entities.push_back(new Entity(models[0], glm::vec3(400.f, 2.f, 398.f)));	//cube 0
	entities.push_back(new Entity(models[0], glm::vec3(398.f, 1.f, 397.f)));	//cube 1
	entities.push_back(new Entity(models[0], glm::vec3(402.f, 1.f, 397.f)));	//cube 2
	
	//entities.push_back(new Entity(models[1], glm::vec3(400.f, 0.05f, 400.f)));	//floor
	
	entities.push_back(new Entity(models[2], glm::vec3(400.f, 7.8f, 360.f)));	//teapot

	// digital grass
	for (int i = 0; i < 400; ++i) {
		float randX = rand() % 40 + 380;
		float randZ = rand() % 40 + 380;
		entities.push_back(new Entity(models[3], glm::vec3(randX, 0.f, randZ)));
	}

	// TERRAIN
	terrain = new Terrain(0, 0, textures[TEX_TERRAIN]);
	models.push_back(new Model(
		terrain->getMesh(),
		terrain->getTexture(),
		textures[0],
		materials[0]
	));
}
void Playground::initLights() {
	float intensity = 1.f;

	lightsPoint.push_back(new LightPoint(
		glm::vec3(410.f, 1.f, 410.f), glm::vec3(1.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(390.f, 1.f, 390.f), glm::vec3(1.f, 0.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(390.f, 1.f, 410.f), glm::vec3(0.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(410.f, 1.f, 390.f), glm::vec3(0.f, 0.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
}
void Playground::initEnviroment() {
	fog = new Fog(0.003, 5.0);
	ambient = glm::vec3(0.10f);
}

////////////////////////////////


Playground::Playground() : Scene() {
	camera = new Camera3D(90.f, 0.1f, 1000.f, glm::vec3(400.f, 1.f, 400.f), glm::vec3(0.f, -90.f, 0.f));
}
Playground::~Playground() {
}

void Playground::update(float dTime) {
	entities[0]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[1]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[2]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));

	//lightSetPosition();
}

void Playground::cameraPanTilt(double mouseOffsetX, double mouseOffsetY) {
	camera->changePanTilt(mouseOffsetX, mouseOffsetY);
}
void Playground::cameraFoward(float dTime)   { camera->moveWalk(dTime*SPEED_MULT, FORWARD);  }
void Playground::cameraBackward(float dTime) { camera->moveWalk(dTime*SPEED_MULT, BACKWARD); }
void Playground::cameraLeft(float dTime)     { camera->moveWalk(dTime*SPEED_MULT, LEFT);     }
void Playground::cameraRight(float dTime)    { camera->moveWalk(dTime*SPEED_MULT, RIGHT);    }
void Playground::cameraUp(float dTime)       { camera->moveWalk(dTime*SPEED_MULT, UP);       }
void Playground::cameraDown(float dTime)     { camera->moveWalk(dTime*SPEED_MULT, DOWN);     }

void Playground::lightSetPosition() { lightsPoint[0]->setPosition(camera->getPosition()); }