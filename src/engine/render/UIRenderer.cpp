#pragma once
#include "UIRenderer.h"

#include "../models/Loader.h"

UIRenderer::UIRenderer(const char* vertexFile, const char* fragFile) 
: shader(UIShader(vertexFile, fragFile)) {
	std::vector<glm::vec2> positions = { {-1,1}, {-1,-1}, {1,1}, {1,-1} };
	quad = Loader::load_simple2D(positions);
}

void UIRenderer::render(std::vector<UI*> uis) {
	shader.use();

	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(quad->getVaoID());
	glEnableVertexAttribArray(0);

	for (auto i : uis) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, i->getTexture()->getID());
		i->updateModelMatrix();
		shader.sendModelMatrix(*&i->getModelMatrix());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVerticesCount());
	}

	glEnable(GL_DEPTH_TEST);

	shader.unuse();
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}