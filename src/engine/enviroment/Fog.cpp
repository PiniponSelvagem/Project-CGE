#include "Fog.h"


Fog::Fog(float density, float gradient) {
	this->density = density;
	this->gradient = gradient;
}

Fog::~Fog() {
}


void Fog::setDensity(float density) {
	this->density = density;
}
void Fog::setGradient(float gradient) {
	this->gradient = gradient;
}

void Fog::sendToShader(Shader &program) {
	program.set1f(density,  "fog.density");
	program.set1f(gradient, "fog.gradient");
}
