#pragma once
#include <engine/Libs.h>

#include <engine/models/Texture.h>
#include <engine/utils/Maths.h>

class UI {
	private:
		Texture* texture;

		glm::vec2 position;
		glm::vec2 origin;
		float rotation;
		glm::vec2 scale;
		glm::mat4 modelMatrix = glm::mat4(0.f);
		bool modelUpdated = true;

	public:
		UI(Texture* texture,
		   glm::vec2 position, glm::vec2 origin = glm::vec2(0.f), float rotation = 0.f, glm::vec2 scale = glm::vec2(1.f)
		);
		virtual ~UI();


		void changePosition(glm::vec2 position);
		void changeOrigin(glm::vec2 origin);
		void changeRotation(float rotation);
		void changeScale(glm::vec2 scale);

		void setPosition(glm::vec2 position);
		void setOrigin(glm::vec2 origin);
		void setRotation(float rotation);
		void setScale(glm::vec2 scale);

		void setPositionX(float x);
		void setPositionY(float y);

		void updateModelMatrix();

		Texture* getTexture();

		glm::vec2 getPosition();
		glm::vec2 getOrigin();
		float getRotation();
		glm::vec2 getScale();

		glm::mat4 getModelMatrix();
};