#pragma once
#include "EntityRenderer.h"

void EntityRenderer::render(Entity* entity) {
	Model* model = entity->getModel();

	shader->setVec3f(model->getMaterial()->getAmbient(),  "material.ambient");
	shader->setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader->setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader->set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader->set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");

	shader->use();

	//diffuseTex->bind(0);
	//bind(const GLint textureUnit)
	//textureunit = 0
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(model->getDiffuseTex()->getType(), model->getDiffuseTex()->getID());
	//textureunit = 1
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(model->getSpecularTex()->getType(), model->getSpecularTex()->getID());



	entity->updateModelMatrix();
	shader->setMat4fv(entity->getModelMatrix(), "ModelMatrix");
	shader->use();

	glBindVertexArray(model->getMesh()->getVaoID());
	//if (nIndices == 0)
	glDrawArrays(GL_TRIANGLES, 0, model->getMesh()->getVertexCount());
	//else
	//	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);



	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}