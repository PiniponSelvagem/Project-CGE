#pragma once
#include "Light.h"



LightPoint::LightPoint(glm::vec3 position, glm::vec3 color, float intensity, float attenuation, float falloffNear, float falloffFar) : Light(position, color, intensity) {
	this->attenuation = attenuation;
	this->falloffNear = falloffNear;
	this->falloffFar  = falloffFar;
}


LightPoint::~LightPoint() {
}


void LightPoint::setAttenuation(float attenuation) {
	if (attenuation < 0.f) {
		this->attenuation = 0.f;
		return;
	}
	this->attenuation = attenuation;
}
void LightPoint::setFalloffNear(float falloffNear) {
	if (falloffNear < 0.f) {
		this->falloffNear = 0.f;
		return;
	}
	this->falloffNear = falloffNear;
}
void LightPoint::setFalloffFar(float falloffFar) {
	if (falloffFar < falloffNear) {
		this->falloffFar = falloffNear;
		return;
	}
	this->falloffFar = falloffNear;
}

/*
float LightPoint::getAttenuation() {
	return attenuation;
}
float LightPoint::getFalloffNear() {
	return falloffNear;
}
float LightPoint::getFalloffFar() {
	return falloffFar;
}
*/

void LightPoint::sendToShader(Shader &program) {
	program.setVec3f(position, "lightPoint.position");
	program.setVec3f(color,    "lightPoint.color");
	program.set1f(intensity,   "lightPoint.intensity");
	program.set1f(attenuation, "lightPoint.attenuation");
	program.set1f(falloffNear, "lightPoint.falloffNear");
	program.set1f(falloffFar,  "lightPoint.falloffFar");
}