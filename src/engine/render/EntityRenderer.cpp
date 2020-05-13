#pragma once
#include "EntityRenderer.h"

void EntityRenderer::sendCamera(Camera &camera) {
	shader.setMat4fv(camera.getViewMatrix(), "ViewMatrix");
	shader.setVec3f(camera.getPosition(), "cameraPos");
	camera.updateProjectionMatrix();
	shader.setMat4fv(camera.getProjectionMatrix(), "ProjectionMatrix");
}

void EntityRenderer::sendFog(Fog &fog) {
	shader.set1f(fog.getDensity(), "fog.density");
	shader.set1f(fog.getGradient(), "fog.gradient");
}

void EntityRenderer::sendAmbient(glm::vec3 &ambient) {
	shader.setVec3f(ambient, "ambient");
}

void EntityRenderer::sendLightsPoint(std::vector<LightPoint*> &lightsPoint) {
	int idx = 0;
	for (LightPoint* lightPoint : lightsPoint) {
		std::string prefix = "lightPoint[" + std::to_string(idx++) + "].";
		shader.setVec3f(lightPoint->getPosition(), (prefix + "position").c_str());
		shader.setVec3f(lightPoint->getColor(), (prefix + "color").c_str());
		shader.set1f(lightPoint->getIntensity(), (prefix + "intensity").c_str());
		shader.set1f(lightPoint->getAttenuation(), (prefix + "attenuation").c_str());
		shader.set1f(lightPoint->getFalloffNear(), (prefix + "falloffNear").c_str());
		shader.set1f(lightPoint->getFalloffFar(), (prefix + "falloffFar").c_str());
	}
}

void EntityRenderer::bindTexture(Texture* texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture->getType(), texture->getID());
}




void EntityRenderer::sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	sendCamera(camera);
	sendFog(fog);
	sendAmbient(ambient);
	sendLightsPoint(lightsPoint);
	shader.unuse();
}

void EntityRenderer::render(Entity* entity) {
	Model* model = entity->getModel();

	shader.use();

	shader.setVec3f(model->getMaterial()->getDiffuse(),  "material.diffuse");
	shader.setVec3f(model->getMaterial()->getSpecular(), "material.specular");
	shader.set1i(model->getMaterial()->getDiffuseTex(),  "material.diffuseTex");
	shader.set1i(model->getMaterial()->getSpecularTex(), "material.specularTex");
	
	bindTexture(model->getDiffuseTex(), 0);
	bindTexture(model->getSpecularTex(), 1);
	
	entity->updateModelMatrix();
	shader.setMat4fv(entity->getModelMatrix(), "ModelMatrix");

	glBindVertexArray(model->getMesh()->getVaoID());

	for (unsigned int i = 0; i <= 2; ++i)
		glEnableVertexAttribArray(i);

	int nIndices = model->getMesh()->getIndicesCount();
	if (nIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, model->getMesh()->getVerticesCount());
	else
		glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

	for (unsigned int i = 0; i <= 2; ++i)
		glDisableVertexAttribArray(i);
	
	
	glBindVertexArray(0);
	shader.unuse();
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}