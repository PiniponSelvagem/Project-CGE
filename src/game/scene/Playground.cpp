#include "Playground.h"

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
	std::vector<Mesh*> meshes;
	std::vector<Mesh*> meshFloor;

	meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	meshFloor.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f, 0.f, -2.f),
			glm::vec3(0.f),
			glm::vec3(-90.f, 0.f, 0.f),
			glm::vec3(55.f)
		)
	);


	models.push_back(new Model(
		glm::vec3(0.f, 0.f, -1.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(0.f, 2.f, 2.f),
		materials[MAT_CRATE],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(-2.f, 2.f, 0.f),
		materials[MAT_CRATE],
		textures[TEX_FRAGILE],
		textures[TEX_FRAGILE_SPECULAR],
		meshes
	));

	models.push_back(new Model(
		glm::vec3(0.f, 0.f, 0.f),
		materials[MAT_CRATE],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
		meshFloor
	));
	
	models.push_back(new Model(
		glm::vec3(0.f, 5.5f, -20.f),
		materials[MAT_CRATE],
		textures[TEX_DEFAULT],
		textures[TEX_DEFAULT],
		"resources/obj/teapot.obj"
	));

	for (auto *&i : meshes) {
		delete i;
	}
	for (auto *&i : meshFloor) {
		delete i;
	}
}
void Playground::initLights() {
	/*
	lightsPoint.push_back(new LightPoint(
		glm::vec3(0.f, 0.f, 1.f)//, glm::vec3(1.f, 0.f, 0.f)
	));
	*/

	lightsPoint.push_back(new LightPoint(
		glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f),
		1.f,
		1.f,
		0.045f, 0.0075f
	));

	/*
	lightsPoint.push_back(new LightPoint(
		glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 0.f, 0.f),
		1.f,
		1.f,
		0.045f, 0.0075f
	));
	/*
	lightsPoint.push_back(new LightPoint(
		glm::vec3(4.f, 0.f, 4.f), glm::vec3(0.f, 1.f, 0.f)
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)
	));
	lightsPoint.push_back(new LightPoint(
		glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f)
	));
	*/
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

void Playground::update() {
	models[0]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
	models[1]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
	models[2]->changeRotation(glm::vec3(0.f, 1.f, 0.f));

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