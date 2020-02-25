#include "SceneGUI.h"

enum shader_enum {
	SHADER_CORE_PROGRAM
};

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

void SceneGUI::initShaders() {
	// SHADER_CORE_PROGRAM
	shaders.push_back(new Shader("resources/shaders/vertex_gui.glsl", "resources/shaders/fragment_gui.glsl"));
}
void SceneGUI::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_specular.png", GL_TEXTURE_2D));
}
void SceneGUI::initMaterials() {
	materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f),
									 0,
									 1
	));
}
void SceneGUI::initModels() {
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

	models.push_back(new Model(
		glm::vec3(50.f, 50.f, -5.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_SPECULAR],
		meshes
	));

	for (auto *&i : meshes) {
		delete i;
	}
}
void SceneGUI::initLights() {
	lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void SceneGUI::initUniforms() {
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(*lights[0], "lightPos0");
}

void SceneGUI::updateUniforms() {
	// Update viewMatrix (camera)
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shaders[SHADER_CORE_PROGRAM]->setVec3f(glm::vec3(0.f, 0.f, 0.f), "cameraPos");
	shaders[SHADER_CORE_PROGRAM]->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}



SceneGUI::SceneGUI() {
	camera = new CameraGUI(800.f, 600.f, 10.f);
}
SceneGUI::~SceneGUI() {
	delete camera;

	for (size_t i = 0; i < shaders.size(); ++i) { delete shaders[i]; }
	for (size_t i = 0; i < textures.size(); ++i) { delete textures[i]; }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (size_t i = 0; i < lights.size(); ++i) { delete lights[i]; }
}

void SceneGUI::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
	initLights();
}

CameraGUI* SceneGUI::getMainCamera() {
	return camera;
}

void SceneGUI::render() {
	updateUniforms();
	for (auto *i : models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}
}