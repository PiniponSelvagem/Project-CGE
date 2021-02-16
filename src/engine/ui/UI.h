#pragma once
#include "../../libs.h"

#include "../models/Texture.h"
#include "../utils/Maths.h"

class UI {
	private:
		Texture* texture;

		glm::vec2 position;
		glm::vec2 origin;
		float rotation;
		glm::vec2 scale;
		glm::mat4 modelMatrix;
		bool modelUpdated = true;

	public:
		UI(Texture* texture,
		   glm::vec2 position, glm::vec2 origin = glm::vec2(0.f), float rotation = 0.f, glm::vec2 scale = glm::vec2(1.f)
		)
			: texture(texture), position(position), origin(origin),	rotation(rotation), scale(scale)
		{ }
		virtual ~UI() { }


		inline void changePosition(glm::vec2 position) { this->position += position; modelUpdated = true; }
		inline void changeOrigin(glm::vec2 origin)     { this->origin += origin;     modelUpdated = true; }
		inline void changeRotation(float rotation) {
			this->rotation += rotation;
			modelUpdated = true;

			if (this->rotation > 360.f || this->rotation < -360.f) this->rotation = 0.f;
		}
		inline void changeScale(glm::vec2 scale) { this->scale += scale; modelUpdated = true; }

		inline void setPosition(glm::vec2 position) { this->position = position; modelUpdated = true; }
		inline void setOrigin(glm::vec2 origin)     { this->origin = origin;     modelUpdated = true; }
		inline void setRotation(float rotation)     { this->rotation = rotation; modelUpdated = true; }
		inline void setScale(glm::vec2 scale)       { this->scale = scale;       modelUpdated = true; }

		inline void setPositionX(float x) { this->position.x = x; modelUpdated = true; }
		inline void setPositionY(float y) { this->position.y = y; modelUpdated = true; }

		void updateModelMatrix();

		inline Texture* getTexture()   { return texture; }

		inline glm::vec2 getPosition() { return position; }
		inline glm::vec2 getOrigin()   { return origin;   }
		inline float getRotation()     { return rotation; }
		inline glm::vec2 getScale()    { return scale;    }

		inline glm::mat4 getModelMatrix() { return modelMatrix; }
};