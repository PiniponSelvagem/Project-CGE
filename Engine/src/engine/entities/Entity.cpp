#pragma once
#include <engine/entities/Entity.h>

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




Entity::Entity(Model* model,
	   glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale,
	   int texIndex
) {
	this->model = model;
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;
	this->texIndex = texIndex;

	texOffsetVector = glm::vec2(getTextureXOffset(), getTextureYOffset());
}
Entity::~Entity() { }

void Entity::setModel(Model* model) { this->model = model; }

void Entity::changePosition(glm::vec3 position) { this->position += position; modelUpdated = true; }
void Entity::changeOrigin(glm::vec3 origin)     { this->origin += origin;     modelUpdated = true; }
void Entity::changeRotation(glm::vec3 rotation) {
	this->rotation += rotation;
	modelUpdated = true;

	if (this->rotation.x > 360.f || this->rotation.x < -360.f) this->rotation.x = 0.f;
	if (this->rotation.y > 360.f || this->rotation.y < -360.f) this->rotation.y = 0.f;
	if (this->rotation.z > 360.f || this->rotation.z < -360.f) this->rotation.z = 0.f;
}
void Entity::changeScale(glm::vec3 scale)    { this->scale += scale;      modelUpdated = true; }

void Entity::setPosition(glm::vec3 position) { this->position = position; modelUpdated = true; }
void Entity::setOrigin(glm::vec3 origin)     { this->origin = origin;     modelUpdated = true; }
void Entity::setRotation(glm::vec3 rotation) { this->rotation = rotation; modelUpdated = true; }
void Entity::setScale(glm::vec3 scale)       { this->scale = scale;       modelUpdated = true; }

void Entity::setPositionX(float x) { this->position.x = x; modelUpdated = true; }
void Entity::setPositionY(float y) { this->position.y = y; modelUpdated = true; }
void Entity::setPositionZ(float z) { this->position.z = z; modelUpdated = true; }

void Entity::setRotationX(float x) { this->rotation.x = x; modelUpdated = true; }
void Entity::setRotationY(float y) { this->rotation.y = y; modelUpdated = true; }
void Entity::setRotationZ(float z) { this->rotation.z = z; modelUpdated = true; }

void Entity::updateModelMatrix() {
	if (modelUpdated) {
		Maths::updateModelMatrix(&modelMatrix, position, rotation, scale, origin);
		modelUpdated = false;
	}
};

Model* Entity::getModel() { return model; }

glm::vec2 Entity::getTextureOffsetVector() { return texOffsetVector; }

glm::vec3 Entity::getPosition() { return position; }
glm::vec3 Entity::getOrigin()   { return origin;   }
glm::vec3 Entity::getRotation() { return rotation; }
glm::vec3 Entity::getScale()    { return scale;    }

glm::mat4 Entity::getModelMatrix() { return modelMatrix; }
