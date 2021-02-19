#pragma once
#include <engine/scene/Scene.h>
#include <engine/models/ObjLoader.h>

void Scene::loadFromFile() {
	std::ifstream inFile(sceneFile);

	if (!inFile.is_open()) {
		throw "ERROR::SCENE::LOADFROMFILE:Could not open file.";
	}

	float terrainSize = -1;

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";

	std::string* shaderUI = new std::string[2];
	std::string* shaderEntity = new std::string[2];
	std::string* shaderTerrain = new std::string[2];

	float worldGravity = 0;

	while (std::getline(inFile, line)) {
		ss.clear();
		ss.str(line);
		if (line.size() > 1) ss >> prefix;
		else prefix = "";

		if (prefix == "shader") {
			std::string type = "";
			ss >> type;
			if (type == "ui") {
				std::string glslFile = "";
				ss >> glslFile;
				shaderUI[0] = glslFile;	// vertex
				ss >> glslFile;
				shaderUI[1] = glslFile;	// fragment
			} else if (type == "core") {
				std::string glslFile = "";
				ss >> glslFile;
				shaderEntity[0] = glslFile;	// vertex
				ss >> glslFile;
				shaderEntity[1] = glslFile;	// fragment
			} else if (type == "terrain") {
				std::string glslFile = "";
				ss >> glslFile;
				shaderTerrain[0] = glslFile;	// vertex
				ss >> glslFile;
				shaderTerrain[1] = glslFile;	// fragment
			}
		}
		else if (prefix == "mesh") {
			std::string type = "";
			ss >> type;
			if (type == "arrays") {
				std::string meshFile;
				ss >> meshFile;
				meshes.push_back(ObjLoader::loadObj_arrays(meshFile.c_str()));
			}
			else if (type == "elements") {
				std::string meshFile;
				ss >> meshFile;
				meshes.push_back(ObjLoader::loadObj(meshFile.c_str()));
			}
		}
		else if (prefix == "texture") {
			std::string texFile;
			int nOfRows;
			ss >> texFile;
			ss >> nOfRows;
			textures.push_back(new Texture(texFile.c_str(), GL_TEXTURE_2D, nOfRows));
		}
		else if (prefix == "terrainTexPack") {
			int* texIdx = new int[8];
			for (int i = 0; i < 8; ++i) {
				int idx;
				ss >> idx;
				if (idx == -1) {
					if ((i % 2) == 0) { texIdx[i] = 0; }	// default diffuse texture
					else { texIdx[i] = 1; }					// default specular texture
				}
				else {
					texIdx[i] = idx+2;	// 2 -> number of default textures previously loaded
				}
			}
			terrainTexPacks.push_back(new TerrainTexturePack(
					textures[texIdx[0]], textures[texIdx[1]],
					textures[texIdx[2]], textures[texIdx[3]],
					textures[texIdx[4]], textures[texIdx[5]],
					textures[texIdx[6]], textures[texIdx[7]]
				)
			);
		}
		else if (prefix == "material") {
			float dif, spec;
			ss >> dif;
			ss >> spec;
			materials.push_back(new Material(glm::vec3(dif), glm::vec3(spec), 0, 1));
		}
		else if (prefix == "model") {
			int mesh, difTex, specTex, mat;
			ss >> mesh;
			ss >> difTex; 
			if (difTex == -1) { difTex = 0;  }	// default diffuse texture
			else { difTex += 2; }				// default texture offset
			ss >> specTex;
			if (specTex == -1) { specTex = 1; }	// default specular texture
			else { specTex += 2; }				// default texture offset
			ss >> mat;
			models.push_back(new Model(meshes[mesh], textures[difTex], textures[specTex], materials[mat]));
		}
		else if (prefix == "terrainSize") {
			if (terrainSize == -1) {
				ss >> terrainSize;
			}
			else {
				float ignoredSize;
				ss >> ignoredSize;
				std::cout << "WARN::SCENE::LOADFROMFILE: Terrain size already set to " << terrainSize << ", ignoring new value " << ignoredSize << std::endl;
			}
		}
		else if (prefix == "terrain") {
			int gridX, gridZ;
			std::string heightMapFile = "";
			float maxHeight;
			int terrainTexPack;
			std::string blendMapFile = "";

			ss >> gridX; ss >> gridZ;
			ss >> heightMapFile;
			ss >> maxHeight;
			ss >> terrainTexPack;
			ss >> blendMapFile;
			terrain = new Terrain(gridX, gridZ, heightMapFile.c_str(), terrainSize, maxHeight,
								  terrainTexPacks[terrainTexPack],
								  new Texture(blendMapFile.c_str(), GL_TEXTURE_2D)
			);
		}
		else if (prefix == "worldGravity") {
			ss >> worldGravity;
			worldGravity *= -50.f;
		}
		else if (prefix == "player") {
			float runSpeed, turnSpeed, jumpPower;
			int modelID;
			glm::vec3 position, origin, rotation, scale;

			ss >> runSpeed;
			ss >> turnSpeed;
			ss >> jumpPower;
			ss >> modelID;
			ss >> position.x >> position.y >> position.z;
			ss >> origin.x >> origin.y >> origin.z;
			ss >> rotation.x >> rotation.y >> rotation.z;
			ss >> scale.x >> scale.y >> scale.z;

			player = new Player(
				runSpeed, turnSpeed, worldGravity, jumpPower,
				models[modelID], position, origin, rotation,
				scale
			);

			entities.push_back(player);
		}
		else if (prefix == "entity") {
			int modelID;
			int useTerrainOffset;
			glm::vec3 position, origin, rotation, scale;
			int texIndex;	// texture number in texture atlas, starts at 0

			ss >> modelID;
			ss >> useTerrainOffset;
			ss >> position.x >> position.y >> position.z;
			ss >> origin.x >> origin.y >> origin.z;
			ss >> rotation.x >> rotation.y >> rotation.z;
			ss >> scale.x >> scale.y >> scale.z;
			ss >> texIndex;

			if (useTerrainOffset == 1) {
				position.y += terrain->getHeight(position.x, position.z);
			}

			entities.push_back(
				new Entity(
					models[modelID],
					position, origin, rotation,
					scale,
					texIndex
				)
			);
		}
		else if (prefix == "light") {
			int useTerrainOffset;
			glm::vec3 position, color;
			float intensity, attenuation, fallOffNear, fallOffFar;

			ss >> useTerrainOffset;
			ss >> position.x >> position.y >> position.z;
			ss >> color.x >> color.y >> color.z;
			ss >> intensity;
			ss >> attenuation;
			ss >> fallOffNear;
			ss >> fallOffFar;

			if (useTerrainOffset == 1) {
				position.y += terrain->getHeight(position.x, position.z);
			}

			lightsPoint.push_back(
					new LightPoint(
					position, color,
					intensity,
					attenuation,
					fallOffNear, fallOffFar
				)
			);
		}
		else if (prefix == "ambient") {
			ss >> ambient.x >> ambient.y >> ambient.z;
		}
		else if (prefix == "fog") {
			float density, gradient;
			ss >> density;
			ss >> gradient;
			fog = new Fog(density, gradient);
		}
		else if (prefix == "camera") {
			std::string type;
			ss >> type;
			
			if (type == "3D_3") {
				float fov, nearPlane, farPlane;
				float playerViewHeight;
				float startDistToPlayer, maxDistToPlayer;
				float startYawToPlayer, startPitchToPlayer;

				ss >> fov;
				ss >> nearPlane;
				ss >> farPlane;
				ss >> playerViewHeight;
				ss >> startDistToPlayer;
				ss >> maxDistToPlayer;
				ss >> startYawToPlayer;
				ss >> startPitchToPlayer;

				camera = new Camera3D_Player3rd(
					*player, playerViewHeight, startDistToPlayer, maxDistToPlayer, startYawToPlayer, startPitchToPlayer,
					fov, nearPlane, farPlane
				);
			}
			else if (type == "3D") {
				float fov, nearPlane, farPlane;
				glm::vec3 position, rotation;

				ss >> fov;
				ss >> nearPlane;
				ss >> farPlane;
				ss >> position.x >> position.y >> position.z;
				ss >> rotation.x >> rotation.y >> rotation.z;

				camera = new Camera3D(
					fov, nearPlane, farPlane, position, rotation
				);
			}
			else if (type == "2D") {
				float fov, nearPlane, farPlane;
				glm::vec3 position, rotation;

				ss >> fov;
				ss >> nearPlane;
				ss >> farPlane;
				ss >> position.x >> position.y >> position.z;
				ss >> rotation.x >> rotation.y >> rotation.z;

				camera = new Camera2D(
					fov, nearPlane, farPlane, position, rotation
				);
			}
		}

		//std::cout << "> " << line << std::endl;
	}

	masterRenderer = new MasterRenderer(
		shaderUI[0].c_str(),      shaderUI[1].c_str(),		// UIShader
		shaderEntity[0].c_str(),  shaderEntity[1].c_str(),	// EntityShader
		shaderTerrain[0].c_str(), shaderTerrain[1].c_str()	// TerrainShader
	);
}



Scene::~Scene() {
	delete camera;

	delete masterRenderer;
	delete terrain;
	for (auto *&i : terrainTexPacks) { delete i; }
	for (auto *&i : meshes) { delete i; }
	for (size_t i = 0; i < textures.size(); ++i)  { delete textures[i];  }
	for (size_t i = 0; i < materials.size(); ++i) { delete materials[i]; }
	for (auto *&i : models) { delete i; }
	for (auto *&i : entities) { delete i; }
	for (size_t i = 0; i < lightsPoint.size(); ++i) { delete lightsPoint[i]; }
	delete fog;
}

void Scene::initScene() {
	textures.push_back(new Texture("resources/png/NO_TEX.png", GL_TEXTURE_2D));
	textures.push_back(new Texture("resources/png/NO_SPECULAR.png", GL_TEXTURE_2D));

	loadFromFile();

	//initRenderer();
	//initMeshes();
	//initTextures();
	//initMaterials();
	//initModels();
	//... initTerrain();
	//initEntities();
	//initLights();
	//initEnviroment();
	//initCamera();

	textures.push_back(new Texture("resources/png/transparency_test.png", GL_TEXTURE_2D));

	//TODO: make this not hardcoded
	ui.push_back(
		new UI(textures[textures.size() - 2],
			   glm::vec2(0.25f, 0.25f), glm::vec2(0.f),
			   0.f,
			   glm::vec2(0.15f, 0.25f)
		)
	);
	ui.push_back(
		new UI(textures[textures.size() - 1],
			   glm::vec2(0.5f, 0.5f), glm::vec2(0.f),
			   0.f,
			   glm::vec2(0.25f, 0.25f)
		)
	);
}

void Scene::reloadShader() {
	std::cout << "SHADER: reloading started..." << std::endl;
	masterRenderer->reloadShaders();
	std::cout << "SHADER: reload complete" << std::endl;
}

Camera* Scene::getMainCamera() {
	return camera;
}

void Scene::render() {
	masterRenderer->render(
		ui,
		*camera, *fog, ambient, lightsPoint,
		entities, *terrain
	);
}