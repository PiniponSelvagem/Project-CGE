#pragma once
#include <engine/shaders/TerrainShader.h>


TerrainShader::TerrainShader(const char* vertexFile, const char* fragmentFile)
	: Shader(vertexFile, fragmentFile) {
}
TerrainShader::~TerrainShader() { }

void TerrainShader::sendCamera(Camera &camera) {
	setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}

void TerrainShader::sendFog(Fog &fog) {
	set1f(fog.getDensity(), "fog.density");
	set1f(fog.getGradient(), "fog.gradient");
}

void TerrainShader::sendAmbient(glm::vec3 &ambient) {
	setVec3f(ambient, "ambient");
}

void TerrainShader::sendLightsPoint(std::vector<LightPoint*> &lightsPoint) {
	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		std::string prefix = "lightPoint[" + std::to_string(idx++) + "].";
		setVec3f(lightPoint->getPosition(), (prefix + "position").c_str());
		setVec3f(lightPoint->getColor(),    (prefix + "color").c_str());
		set1f(lightPoint->getIntensity(),   (prefix + "intensity").c_str());
		set1f(lightPoint->getAttenuation(), (prefix + "attenuation").c_str());
		set1f(lightPoint->getFalloffNear(), (prefix + "falloffNear").c_str());
		set1f(lightPoint->getFalloffFar(),  (prefix + "falloffFar").c_str());
	}
}

void TerrainShader::sendTerrainData(Terrain& terrain) {
	set1i(0, "backTex");	set1i(1, "backTexSpecular");
	set1i(2, "rTex");		set1i(3, "rTexSpecular");
	set1i(4, "gTex");		set1i(5, "gTexSpecular");
	set1i(6, "bTex");		set1i(7, "bTexSpecular");
	set1i(8, "blendMap");
	set1f((GLfloat)terrain.getVertexCount(), "vertexCount");
}

void TerrainShader::sendModelMatrix(glm::mat4& modelMatrix) {
	setMat4fv(modelMatrix, "ModelMatrix");
}