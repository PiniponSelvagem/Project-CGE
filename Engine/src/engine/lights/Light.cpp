#pragma once
#include <engine/lights/Light.h>


Light::Light(glm::vec3 position, glm::vec3 color, float intensity) {
	this->position = position;
	this->color = color;
	this->intensity = intensity;
}
Light::~Light() { }

void Light::setPosition(const glm::vec3 position) { this->position = position;   }
void Light::setColor(const glm::vec3 color)       { this->color = color;         }
void Light::setIntensity(const float intensity)   { this->intensity = intensity; }

glm::vec3 Light::getPosition() { return position;  }
glm::vec3 Light::getColor()    { return color;     }
float Light::getIntensity()    { return intensity; }