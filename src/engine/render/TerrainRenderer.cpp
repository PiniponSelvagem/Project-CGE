#pragma once
#include "TerrainRenderer.h"

void TerrainRenderer::bindTextures(Terrain& terrain) {
	TerrainTexturePack& texturePack = *terrain.getTexturePack();

	glActiveTexture(GL_TEXTURE0);	// Background Texture Diffuse
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackTex()->getID());

	glActiveTexture(GL_TEXTURE1);	// Background Texture Specular
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackTexSpecular()->getID());


	glActiveTexture(GL_TEXTURE2);	// Red Texture Diffuse
	glBindTexture(GL_TEXTURE_2D, texturePack.getRTex()->getID());

	glActiveTexture(GL_TEXTURE3);	// Red Texture Specular
	glBindTexture(GL_TEXTURE_2D, texturePack.getRTexSpecular()->getID());


	glActiveTexture(GL_TEXTURE4);	// Green Texture Diffuse
	glBindTexture(GL_TEXTURE_2D, texturePack.getGTex()->getID());

	glActiveTexture(GL_TEXTURE5);	// Green Texture Specular
	glBindTexture(GL_TEXTURE_2D, texturePack.getGTexSpecular()->getID());


	glActiveTexture(GL_TEXTURE6);	// Blue Texture Diffuse
	glBindTexture(GL_TEXTURE_2D, texturePack.getBTex()->getID());

	glActiveTexture(GL_TEXTURE7);	// Blue Texture Specular
	glBindTexture(GL_TEXTURE_2D, texturePack.getBTexSpecular()->getID());


	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, terrain.getBlendMap()->getID());
}



void TerrainRenderer::sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	shader.sendCamera(camera);
	shader.sendFog(fog);
	shader.sendAmbient(ambient);
	shader.sendLightsPoint(lightsPoint);
	shader.unuse();
}

void TerrainRenderer::render(Terrain& terrain) {
	shader.use();
	shader.sendTerrainData(terrain);

	/*
	shader.setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader.setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader.set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader.set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");
	*/

	bindTextures(terrain);
	//bindTexture(model->getSpecularTex(), 1);

	shader.sendModelMatrix(*&terrain.getModelMatrix());

	glBindVertexArray(terrain.getMesh()->getVaoID());

	for (unsigned int i = 0; i <= 2; ++i)
		glEnableVertexAttribArray(i);

	int nIndices = terrain.getMesh()->getIndicesCount();
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

	for (unsigned int i = 0; i <= 2; ++i)
		glDisableVertexAttribArray(i);


	glBindVertexArray(0);
	shader.unuse();
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}