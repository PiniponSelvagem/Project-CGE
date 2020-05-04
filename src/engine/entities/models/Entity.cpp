#pragma once
#include "../../../libs.h"
#include "Entity.h"

void Entity::updateModelMatrix() {
	modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(modelMatrix, position); //modelMatrix = glm::translate(modelMatrix, origin);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//X
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//Y
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//Z
	modelMatrix = glm::translate(modelMatrix, origin); //modelMatrix = glm::translate(modelMatrix, position - origin);
	modelMatrix = glm::scale(modelMatrix, scale);
};
