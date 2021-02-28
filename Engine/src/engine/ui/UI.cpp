#pragma once
#include <engine/ui/UI.h>


UI::UI(Texture* texture,
   glm::vec2 position, glm::vec2 origin, float rotation, glm::vec2 scale
) : texture(texture), position(position), origin(origin), rotation(rotation), scale(scale) { }
UI::~UI() { }


void UI::changePosition(glm::vec2 position) { this->position += position; modelUpdated = true; }
void UI::changeOrigin(glm::vec2 origin)     { this->origin += origin;     modelUpdated = true; }
void UI::changeRotation(float rotation) {
	this->rotation += rotation;
	modelUpdated = true;

	if (this->rotation > 360.f || this->rotation < -360.f) this->rotation = 0.f;
}
void UI::changeScale(glm::vec2 scale) { this->scale += scale; modelUpdated = true; }

void UI::setPosition(glm::vec2 position) { this->position = position; modelUpdated = true; }
void UI::setOrigin(glm::vec2 origin)     { this->origin = origin;     modelUpdated = true; }
void UI::setRotation(float rotation)     { this->rotation = rotation; modelUpdated = true; }
void UI::setScale(glm::vec2 scale)       { this->scale = scale;       modelUpdated = true; }

void UI::setPositionX(float x) { this->position.x = x; modelUpdated = true; }
void UI::setPositionY(float y) { this->position.y = y; modelUpdated = true; }

void UI::updateModelMatrix() {
	if (modelUpdated) {
		Maths::updateModelMatrix(
			&modelMatrix,
			glm::vec3(position, 0.f),
			glm::vec3(rotation, 0.f, 0.f),
			glm::vec3(scale, 0.f),
			glm::vec3(origin, 0.f)
		);
		modelUpdated = false;
	}
};

Texture* UI::getTexture() { return texture; }

glm::vec2 UI::getPosition() { return position; }
glm::vec2 UI::getOrigin()   { return origin;   }
float UI::getRotation()     { return rotation; }
glm::vec2 UI::getScale()    { return scale;    }

glm::mat4 UI::getModelMatrix() { return modelMatrix; }
