#include "PerformanceTest.h"
#include "../../engine/entities/models/ObjLoader.h"

#define ENTITIES_NUMBER 500
#define ENTITIES_RANGE 50
#define ENTITIES_RANGE_OFFSET ENTITIES_RANGE/2

enum shader_enum {
	SHADER_CORE_PROGRAM
};

enum texture_enum {
	TEX_DEFAULT,
	TEX_CRATE, TEX_CRATE_SPECULAR
};

enum material_enum {
	MAT_CRATE
};

enum mesh_enum {
	MESH_CUBE
};

void PerformanceTest::initShaders() {
	// SHADER_CORE_PROGRAM
	shaders.push_back(new Shader("resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));

	// Renderers
	masterRenderer = new MasterRenderer(shaders[SHADER_CORE_PROGRAM]);
	entityRenderer = new EntityRenderer(shaders[SHADER_CORE_PROGRAM]);
}
void PerformanceTest::initMeshes() {
	std::vector<Vertex> vertex = ObjLoader::loadObj("resources/obj/cube.obj");
	meshes.push_back(new Mesh(
		vertex.data(),
		vertex.size(),
		NULL,
		0
	));
}
void PerformanceTest::initTextures() {
	// TEXTURE - DEFAULT
	textures.push_back(new Texture("resources/png/NO_TEX.png", GL_TEXTURE_2D));

	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));
}
void PerformanceTest::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.05f), glm::vec3(1.f), glm::vec3(2.f),
									 0,
									 1
	));
}
void PerformanceTest::initModels() {
	models.push_back(new Model(
		meshes[0],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		materials[MAT_CRATE]
	));
}
void PerformanceTest::initEntities() {
	for (int i = 0; i < ENTITIES_NUMBER; ++i) {
		float randX = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		float randY = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		float randZ = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		entities.push_back(new Entity(models[0], glm::vec3(randX, randY, randZ)));
	}
}
void PerformanceTest::initLights() {
	float intensity = 0.5f;

	lightsPoint.push_back(new LightPoint(
		glm::vec3(20.f, 0.f, 10.f), glm::vec3(1.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-20.f, 0.f, 20.f), glm::vec3(1.f, 0.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-20.f, 0.f, -20.f), glm::vec3(0.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(20.f, 0.f, -20.f), glm::vec3(0.f, 0.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
}
void PerformanceTest::initEnviroment() {
	fog = new Fog(0.003, 5.0);
}

////////////////////////////////


PerformanceTest::PerformanceTest() : Scene() {
	camera = new Camera3D(90.f, 0.1f, 1000.f, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -90.f, 0.f));
}
PerformanceTest::~PerformanceTest() {
}

void PerformanceTest::update(float dTime) {
	/*
	for (int i = 0; i < ENTITIES_NUMBER; ++i) {
		entities[i]->changeRotation(glm::vec3(dTime*10, dTime*10, dTime*10));
	}
	*/
}

void PerformanceTest::cameraPanTilt(float dTime, double mouseOffsetX, double mouseOffsetY) {
	camera->changePanTilt(dTime, mouseOffsetX, mouseOffsetY);
}
void PerformanceTest::cameraFoward(float dTime)   { camera->moveWalk(dTime, FORWARD);  }
void PerformanceTest::cameraBackward(float dTime) { camera->moveWalk(dTime, BACKWARD); }
void PerformanceTest::cameraLeft(float dTime)     { camera->moveWalk(dTime, LEFT);     }
void PerformanceTest::cameraRight(float dTime)    { camera->moveWalk(dTime, RIGHT);    }
void PerformanceTest::cameraUp(float dTime)       { camera->moveWalk(dTime, UP);       }
void PerformanceTest::cameraDown(float dTime)     { camera->moveWalk(dTime, DOWN);     }