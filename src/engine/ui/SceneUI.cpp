#include "SceneUI.h"

enum texture_enum {
	TEX_CRATE, TEX_CRATE_MASK
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE
};


void SceneUI::initShaders() {
	// SHADER_CORE_PROGRAM
	shader = new Shader("resources/shaders/vertex_gui.glsl", "resources/shaders/fragment_gui.glsl");
}
void SceneUI::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_mask.png", GL_TEXTURE_2D));
}
void SceneUI::initMaterials() {
	materials.push_back(new MaterialUI(
		TEX_CRATE, 
		glm::vec3(1.f, 0.f, 0.f), TEX_CRATE_MASK
	));
}
void SceneUI::initModels() {
	std::vector<Mesh*> meshes;

	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(100.f)
		)
	);

	models.push_back(new ModelUI(
		glm::vec3(100.f, 100.f, -1.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_MASK],
		meshes
	));

	models.push_back(new ModelUI(
		glm::vec3(125.f, 125.f, -2.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE_MASK],
		textures[TEX_CRATE_MASK],
		meshes
	));

	for (auto *&i : meshes) {
		delete i;
	}
}

void SceneUI::initUniforms() {
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}

void SceneUI::updateUniforms() {
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}



SceneUI::SceneUI() {
	camera = new CameraUI(800.f, 600.f, 10.f);
}
SceneUI::~SceneUI() {
	delete camera;
	delete shader;
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
}

void SceneUI::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
}

CameraUI* SceneUI::getMainCamera() {
	return camera;
}

void SceneUI::update() {
	//models[0]->changeRotation(glm::vec3(0.f, 0.f, 1.f));
}

void SceneUI::render() {
	glDisable(GL_DEPTH_TEST);
	updateUniforms();
	for (auto *i : models) {
		i->render(shader);
	}
	glEnable(GL_DEPTH_TEST);
}