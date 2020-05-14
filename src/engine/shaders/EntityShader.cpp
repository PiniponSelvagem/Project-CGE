#pragma once
#include "EntityShader.h"

void EntityShader::sendCamera(Camera &camera) {
	setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}

void EntityShader::sendFog(Fog &fog) {
	set1f(fog.getDensity(), "fog.density");
	set1f(fog.getGradient(), "fog.gradient");
}

void EntityShader::sendAmbient(glm::vec3 &ambient) {
	setVec3f(ambient, "ambient");
}

void EntityShader::sendLightsPoint(std::vector<LightPoint*> &lightsPoint) {
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

void EntityShader::sendMaterial(Material& material) {
	setVec3f(material.getDiffuse(),  "material.diffuse");
	setVec3f(material.getSpecular(), "material.specular");
	set1i(material.getDiffuseTex(),  "material.diffuseTex");
	set1i(material.getSpecularTex(), "material.specularTex");
}

void EntityShader::sendModelMatrix(glm::mat4& modelMatrix) {
	setMat4fv(modelMatrix, "ModelMatrix");
}