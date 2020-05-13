#pragma once
#include "TerrainRenderer.h"

void TerrainRenderer::sendCamera(Camera &camera) {
	shader.setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	shader.setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	shader.setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}

void TerrainRenderer::sendFog(Fog &fog) {
	shader.set1f(fog.getDensity(), "fog.density");
	shader.set1f(fog.getGradient(), "fog.gradient");
}

void TerrainRenderer::sendAmbient(glm::vec3 &ambient) {
	shader.setVec3f(ambient, "ambient");
}

void TerrainRenderer::sendLightsPoint(std::vector<LightPoint*> &lightsPoint) {
	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		std::string prefix = "lightPoint[" + std::to_string(idx++) + "].";
		shader.setVec3f(lightPoint->getPosition(), (prefix + "position").c_str());
		shader.setVec3f(lightPoint->getColor(),    (prefix + "color").c_str());
		shader.set1f(lightPoint->getIntensity(),   (prefix + "intensity").c_str());
		shader.set1f(lightPoint->getAttenuation(), (prefix + "attenuation").c_str());
		shader.set1f(lightPoint->getFalloffNear(), (prefix + "falloffNear").c_str());
		shader.set1f(lightPoint->getFalloffFar(),  (prefix + "falloffFar").c_str());
	}
}

void TerrainRenderer::bindTexture(Texture* texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture->getType(), texture->getID());
}




void TerrainRenderer::sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	sendCamera(camera);
	sendFog(fog);
	sendAmbient(ambient);
	sendLightsPoint(lightsPoint);
	shader.unuse();
}

void TerrainRenderer::render(Terrain* terrain) {
	shader.use();
	shader.set1f(terrain->getVertexCount(), "vertexCount");

	//shader.set1i(terrain->getTexture(), "diffuseTex");
	shader.set1i(0, "diffuseTex");

	/*
	shader.setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader.setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader.set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader.set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");
	*/

	bindTexture(terrain->getTexture(), 0);
	//bindTexture(model->getSpecularTex(), 1);

	shader.setMat4fv(terrain->getModelMatrix(), "ModelMatrix");

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