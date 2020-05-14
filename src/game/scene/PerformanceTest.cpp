#include "PerformanceTest.h"
#include "../../engine/entities/models/ObjLoader.h"

#define LIGHT_POS 10.f
#define LIGHT_INTENSITY 1.f

#define ENTITIES_NUMBER 1000
#define ENTITIES_RANGE 50
#define ENTITIES_RANGE_OFFSET ENTITIES_RANGE/2

/*
#define SPACING 10
#define MAX 10
#define OFFSET (MAX*SPACING)*0.5
*/

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

void PerformanceTest::initRenderer() {
	// SHADER_CORE_PROGRAM
	shaders.push_back(new Shader("resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));
	shaders.push_back(new Shader("resources/shaders/vertex_terrain.glsl", "resources/shaders/fragment_terrain.glsl"));

	// Renderers
	masterRenderer = new MasterRenderer(shaders[0], shaders[1]);
}
void PerformanceTest::initMeshes() {
	meshes.push_back(ObjLoader::loadObj_arrays("resources/obj/cube.obj"));
}
void PerformanceTest::initTextures() {
	// TEXTURE - DEFAULT
	textures.push_back(new Texture("resources/png/NO_TEX.png", GL_TEXTURE_2D));

	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));
}
void PerformanceTest::initMaterials() {
	materials.push_back(new Material(
		glm::vec3(1.f),
		glm::vec3(2.f),
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
	//entities.push_back(new Entity(models[0], glm::vec3(0, 0, -1)));
	
	for (int i = 0; i < ENTITIES_NUMBER; ++i) {
		float randX = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		float randY = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		float randZ = rand() % ENTITIES_RANGE - ENTITIES_RANGE_OFFSET;
		entities.push_back(new Entity(models[0], glm::vec3(randX, randY, randZ)));
	}
	
	// TERRAIN
	terrain = new Terrain(0, 1, textures[1]);
	models.push_back(new Model(
		terrain->getMesh(),
		terrain->getTexture(),
		textures[0],
		materials[0]
	));
	
	/*
	for (int x = 0; x < MAX * SPACING; x+=SPACING) {
		for (int y = 0; y < MAX * SPACING; y+=SPACING) {
			for (int z = 0; z < MAX * SPACING; z+=SPACING) {
				entities.push_back(new Entity(models[0], glm::vec3(
					x-OFFSET, 
					y-OFFSET, 
					z-OFFSET)
				));
			}
		}
	}
	*/
}
void PerformanceTest::initLights() {
	float intensity = LIGHT_INTENSITY;

	lightsPoint.push_back(new LightPoint(
		glm::vec3(LIGHT_POS, 0.f, LIGHT_POS), glm::vec3(1.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-LIGHT_POS, 0.f, LIGHT_POS), glm::vec3(1.f, 0.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(-LIGHT_POS, 0.f, -LIGHT_POS), glm::vec3(0.f, 1.f, 0.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(LIGHT_POS, 0.f, -LIGHT_POS), glm::vec3(0.f, 0.f, 1.f),
		intensity,
		1.f,
		0.045f, 0.0075f
	));
}
void PerformanceTest::initEnviroment() {
	fog = new Fog(0.003, 5.0);
	ambient = glm::vec3(0.05f);
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

void PerformanceTest::cameraPanTilt(double mouseOffsetX, double mouseOffsetY) {
	camera->changePanTilt(mouseOffsetX, mouseOffsetY);
}
void PerformanceTest::cameraFoward(float dTime)   { camera->moveWalk(dTime, FORWARD);  }
void PerformanceTest::cameraBackward(float dTime) { camera->moveWalk(dTime, BACKWARD); }
void PerformanceTest::cameraLeft(float dTime)     { camera->moveWalk(dTime, LEFT);     }
void PerformanceTest::cameraRight(float dTime)    { camera->moveWalk(dTime, RIGHT);    }
void PerformanceTest::cameraUp(float dTime)       { camera->moveWalk(dTime, UP);       }
void PerformanceTest::cameraDown(float dTime)     { camera->moveWalk(dTime, DOWN);     }