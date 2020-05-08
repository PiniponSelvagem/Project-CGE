#pragma once
#include "EntityRenderer.h"

void EntityRenderer::bindTexture(Texture* texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture->getType(), texture->getID());
}



void EntityRenderer::render(Entity* entity) {
	Model* model = entity->getModel();

	shader->setVec3f(model->getMaterial()->getAmbient(),  "material.ambient");
	shader->setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader->setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader->set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader->set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");

	shader->use();

	bindTexture(model->getDiffuseTex(), 0);
	bindTexture(model->getSpecularTex(), 1);


	entity->updateModelMatrix();
	shader->setMat4fv(entity->getModelMatrix(), "ModelMatrix");
	shader->use();

	glBindVertexArray(model->getMesh()->getVaoID());


	// INDICES NOT BEING LOADED ATM IN OBJLOADER.cpp

	//if (nIndices == 0)
	glDrawArrays(GL_TRIANGLES, 0, model->getMesh()->getVertexCount());
	//else
	//	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, model->getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0);
	
	
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}