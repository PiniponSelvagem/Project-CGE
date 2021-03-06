#pragma once
#include <engine/render/EntityRenderer.h>

void EntityRenderer::bindTexture(Texture* texture, int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(texture->getType(), texture->getID());
}



EntityRenderer::EntityRenderer(const char* vertexFile, const char* fragFile) : shader(EntityShader(vertexFile, fragFile)) {
}

void EntityRenderer::sendToShader(Camera &camera, Fog &fog, glm::vec3 &ambient, std::vector<LightPoint*> &lightsPoint) {
	shader.use();
	shader.sendCamera(camera);
	shader.sendCamera(camera);
	shader.sendFog(fog);
	shader.sendAmbient(ambient);
	shader.sendLightsPoint(lightsPoint);
	shader.unuse();
}

void EntityRenderer::reloadShader() {
	shader.reload();
}

void EntityRenderer::render(Entity* entity) {
	Model* model = entity->getModel();

	shader.use();
	shader.sendMaterial(*model->getMaterial());
	shader.sendTextureInfo(*model->getDiffuseTex(), entity->getTextureOffsetVector());
	
	bindTexture(model->getDiffuseTex(), 0);
	bindTexture(model->getSpecularTex(), 1);
	
	entity->updateModelMatrix();
	shader.sendModelMatrix(*&entity->getModelMatrix());

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