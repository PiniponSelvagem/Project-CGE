#include "SceneGUI.h"

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


void SceneGUI::initShaders() {
	// SHADER_CORE_PROGRAM
	shader = new Shader("resources/shaders/vertex_gui.glsl", "resources/shaders/fragment_gui.glsl");
}
void SceneGUI::initTextures() {
	// TEXTURE 0
	textures.push_back(new Texture("resources/png/crate.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/crate_mask.png", GL_TEXTURE_2D));
}
void SceneGUI::initMaterials() {
	materials.push_back(new MaterialGUI(
		TEX_CRATE, 
		glm::vec3(1.f, 0.f, 0.f), TEX_CRATE_MASK
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

	models.push_back(new ModelGUI(
		glm::vec3(100.f, 100.f, -1.f),
		materials[MAT_CRATE],
		textures[TEX_CRATE],
		textures[TEX_CRATE_MASK],
		meshes
	));

	for (auto *&i : meshes) {
		delete i;
	}
}

void SceneGUI::initUniforms() {
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}

void SceneGUI::updateUniforms() {
	// Update viewMatrix (camera)
	shader->setMat4fv(camera->getViewMatrix(), "ViewMatrix");
	shader->setMat4fv(camera->getProjectionMatrix(), "ProjectionMatrix");
}



SceneGUI::SceneGUI() {
	camera = new CameraGUI(800.f, 600.f, 10.f);
}
SceneGUI::~SceneGUI() {
	delete camera;
	delete shader;
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
}

void SceneGUI::initScene() {
	initShaders();
	initTextures();
	initMaterials();
	initModels();
}

CameraGUI* SceneGUI::getMainCamera() {
	return camera;
}

void SceneGUI::update() {
	//models[0]->changeRotation(glm::vec3(0.f, 0.f, 1.f));
}

void SceneGUI::render() {
	updateUniforms();
	for (auto *i : models) {
		i->render(shader);
	}
}