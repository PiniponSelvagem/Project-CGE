#pragma once
#include "Entity.h"

float Entity::getTextureXOffset() {
	float nOfRows = model->getDiffuseTex()->getNOfRows();
	float column = texIndex % (int)nOfRows;
	return column / nOfRows;
}

float Entity::getTextureYOffset() {
	float nOfRows = model->getDiffuseTex()->getNOfRows();
	int row = texIndex / nOfRows;
	return (float)row / nOfRows;
}



void Entity::updateModelMatrix() {
	if (modelUpdated) {
		Maths::updateModelMatrix(&modelMatrix, position, rotation, scale, origin);
		modelUpdated = false;
	}
};
