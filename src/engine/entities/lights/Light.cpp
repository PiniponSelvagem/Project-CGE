#pragma once
#include "Light.h"



Light::Light(glm::vec3 position, glm::vec3 color, float intensity) {
	this->position = position;
	this->color = color;
	this->intensity = intensity;
}


Light::~Light() {
}


void Light::setPosition(glm::vec3 position) {
	this->position = position;
}
void Light::setColor(glm::vec3 color) {
	this->color = color;
}
void Light::serIntensity(float intensity) {
	this->intensity = intensity;
}

glm::vec3 Light::getPosition() {
	return position;
}
glm::vec3 Light::getColor() {
	return color;
}
float Light::getIntensity() {
	return intensity;
}

void Light::sendToShader(Shader &program) {
	program.setVec3f(position, "light.position");
	program.setVec3f(color, "light.color");
	program.set1f(intensity, "light.intensity");
}