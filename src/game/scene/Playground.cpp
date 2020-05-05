#include "Playground.h"
#include "../../engine/entities/models/ObjLoader.h"

enum shader_enum {
	SHADER_CORE_PROGRAM
};

enum texture_enum {
	TEX_DEFAULT,
	TEX_CRATE, TEX_CRATE_SPECULAR,
	TEX_FRAGILE, TEX_FRAGILE_SPECULAR,
	TEX_GRASS, TEX_GRASS_SPECULAR
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE,
	MESH_QUAD
};

void Playground::initShaders() {
	// SHADER_CORE_PROGRAM
	shaders.push_back(new Shader("resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));

	// Renderers
	masterRenderer = new MasterRenderer(shaders[SHADER_CORE_PROGRAM]);
	entityRenderer = new EntityRenderer(shaders[SHADER_CORE_PROGRAM]);
}
void Playground::initMeshes() {
	std::vector<Vertex> vertex = ObjLoader::loadObj("resources/obj/cube.obj");
	meshes.push_back(new Mesh(
		vertex.data(),
		vertex.size(),
		NULL,
		0
	));

	vertex = ObjLoader::loadObj("resources/obj/floor.obj");
	meshes.push_back(new Mesh(
		vertex.data(),
		vertex.size(),
		NULL,
		0
	));

	vertex = ObjLoader::loadObj("resources/obj/teapot.obj");
	meshes.push_back(new Mesh(
		vertex.data(),
		vertex.size(),
		NULL,
		0
	));
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

	// TEXTURE 1
	textures.push_back(new Texture("resources/png/grass.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/grass_specular.png", GL_TEXTURE_2D));
}
void Playground::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.05f), glm::vec3(1.f), glm::vec3(2.f),
		0,
		1
	));
}
void Playground::initModels() {
	models.push_back(new Model(
		meshes[0],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		materials[MAT_CRATE]
	));

	models.push_back(new Model(
		meshes[1],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
		materials[MAT_CRATE]
	));

	models.push_back(new Model(
		meshes[2],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
		materials[MAT_CRATE]
	));
}
void Playground::initEntities() {
	entities.push_back(new Entity(models[0], glm::vec3(0.f, 0.f, -1.f)));	//cube 0
	entities.push_back(new Entity(models[0], glm::vec3(0.f, 2.f, 2.f)));	//cube 1
	entities.push_back(new Entity(models[0], glm::vec3(-2.f, 2.f, 0.f)));	//cube 2

	entities.push_back(new Entity(models[1], glm::vec3(0.f, -2.f, 0.f)));	//floor

	entities.push_back(new Entity(models[2], glm::vec3(0.f, 5.5f, -20.f)));	//teapot
}
void Playground::initLights() {
	/*
	lightsPoint.push_back(new LightPoint(
		glm::vec3(0.f, 0.f, 1.f)//, glm::vec3(1.f, 0.f, 0.f)
	));
	*/
	float intensity = 0.5f;

	lightsPoint.push_back(new LightPoint(
		glm::vec3(10.f, 0.f, 10.f), glm::vec3(1.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-10.f, 0.f, 10.f), glm::vec3(1.f, 0.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-10.f, 0.f, -10.f), glm::vec3(0.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(10.f, 0.f, -10.f), glm::vec3(0.f, 0.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
}
void Playground::initEnviroment() {
	fog = new Fog(0.003, 5.0);
}

////////////////////////////////


Playground::Playground() : Scene() {
	camera = new Camera3D(90.f, 0.1f, 1000.f, glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, -90.f, 0.f));
}
Playground::~Playground() {
}

void Playground::update(float dTime) {
	entities[0]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[1]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));
	entities[2]->changeRotation(glm::vec3(0.f, dTime*20.f, 0.f));

	//lightSetPosition();
}

void Playground::cameraPanTilt(float dTime, double mouseOffsetX, double mouseOffsetY) {
	camera->changePanTilt(dTime, mouseOffsetX, mouseOffsetY);
}
void Playground::cameraFoward(float dTime)   { camera->moveWalk(dTime, FORWARD);  }
void Playground::cameraBackward(float dTime) { camera->moveWalk(dTime, BACKWARD); }
void Playground::cameraLeft(float dTime)     { camera->moveWalk(dTime, LEFT);     }
void Playground::cameraRight(float dTime)    { camera->moveWalk(dTime, RIGHT);    }
void Playground::cameraUp(float dTime)       { camera->moveWalk(dTime, UP);       }
void Playground::cameraDown(float dTime)     { camera->moveWalk(dTime, DOWN);     }

void Playground::lightSetPosition() { lightsPoint[0]->setPosition(camera->getPosition()); }