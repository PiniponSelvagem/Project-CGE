#pragma once
#include <engine/enviroment/Fog.h>


Fog::Fog(float density, float gradient) {
	this->density = density;
	this->gradient = gradient;
}
Fog::~Fog() { }

void Fog::setDensity(float density)   { this->density = density;   }
void Fog::setGradient(float gradient) { this->gradient = gradient; }

float Fog::getDensity()  { return density; }
float Fog::getGradient() { return gradient; }