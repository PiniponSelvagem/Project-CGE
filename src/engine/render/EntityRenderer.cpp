#pragma once
#include "EntityRenderer.h"

void EntityRenderer::bindModel(Model &model) {
	shader->setVec3f(model.getMaterial().getAmbient(),  "material.ambient");
	shader->setVec3f(model.getMaterial().getDiffuse(),  "material.diffuse");
	shader->setVec3f(model.getMaterial().getSpecular(), "material.specular");
	shader->set1i(model.getMaterial().getDiffuseTex(),  "material.diffuseTex");
	shader->set1i(model.getMaterial().getSpecularTex(), "material.specularTex");

	shader->use();
	bindTexture(model.getDiffuseTex(), 0);
	bindTexture(model.getSpecularTex(), 1);
	
	glBindVertexArray(model.getMesh().getVaoID());

	for (unsigned int i = 0; i <= 2; ++i)
		glEnableVertexAttribArray(i);
}

void EntityRenderer::bindTexture(Texture &texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture.getType(), texture.getID());
}

void EntityRenderer::renderEntity(Entity &entity, int nVertices, int nIndices) {
	entity.updateModelMatrix();
	shader->setMat4fv(entity.getModelMatrix(), "ModelMatrix");

	shader->use();

	if (nIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, nVertices);
	else
		glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
}

void EntityRenderer::unbindModel() {
	for (unsigned int i = 0; i <= 2; ++i)
		glDisableVertexAttribArray(i);

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}




void EntityRenderer::render(modelEntity_map &entities) {
	// Loop through the keys
	// key.first = Model, key.second = entities vector
	for (auto &key : entities) {
		Model model = key.first;
		bindModel(model);
		for (Entity entity : key.second)
			renderEntity(entity, key.first.getMesh().getVerticesCount(), key.first.getMesh().getIndicesCount());
		unbindModel();
	}
}