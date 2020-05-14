#pragma once
#include "TerrainShader.h"

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
	set1i(0, "diffuseTex");
	set1f(terrain.getVertexCount(), "vertexCount");
}

void TerrainShader::sendModelMatrix(glm::mat4& modelMatrix) {
	setMat4fv(modelMatrix, "ModelMatrix");
}