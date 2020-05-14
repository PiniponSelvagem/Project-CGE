#pragma once
#include "TerrainRenderer.h"

void TerrainRenderer::bindTexture(Texture* texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture->getType(), texture->getID());
}



void TerrainRenderer::sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	shader.sendCamera(camera);
	shader.sendFog(fog);
	shader.sendAmbient(ambient);
	shader.sendLightsPoint(lightsPoint);
	shader.unuse();
}

void TerrainRenderer::render(Terrain* terrain) {
	shader.use();
	shader.sendTerrainData(*terrain);

	/*
	shader.setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader.setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader.set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader.set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");
	*/

	bindTexture(terrain->getTexture(), 0);
	//bindTexture(model->getSpecularTex(), 1);

	shader.sendModelMatrix(*&terrain->getModelMatrix());

	glBindVertexArray(terrain->getMesh()->getVaoID());

	for (unsigned int i = 0; i <= 2; ++i)
		glEnableVertexAttribArray(i);

	int nIndices = terrain->getMesh()->getIndicesCount();
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

	for (unsigned int i = 0; i <= 2; ++i)
		glDisableVertexAttribArray(i);


	glBindVertexArray(0);
	shader.unuse();
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}