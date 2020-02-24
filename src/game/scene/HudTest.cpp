#include "HudTest.h"

enum texture_enum {
	TEX_CRATE, TEX_CRATE_SPECULAR
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE
};

void HudTest::initShaders() {
	// SHADER_CORE_PROGRAM
	shaders.push_back(new Shader("resources/shaders/vertex_core.glsl", "resources/shaders/fragment_core.glsl"));
}
void HudTest::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));
}
void HudTest::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f),
		0,
		1
	));
}
void HudTest::initModels() {
	std::vector<Mesh*> meshes;

	meshes.push_back(
		new Mesh(
			&Cube(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	models.push_back(new Model(
		glm::vec3(2.f, -2.f, -5.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		meshes
	));

	for (auto *&i : meshes) {
		delete i;
	}
}
void HudTest::initLights() {
	lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}



HudTest::HudTest() : Scene() {
	camera = new Camera3D(90.f, 0.1f, 1000.f, glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, -90.f, 0.f));
}


HudTest::~HudTest() {
}

void HudTest::update() {
	models[0]->changeRotation(glm::vec3(0.f, 1.f, 0.f));
}
