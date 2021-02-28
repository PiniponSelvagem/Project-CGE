#pragma once
#include <engine/Libs.h>
#include <engine/utils/Maths.h>
#include <engine/models/Model.h>

class Entity {
	private:
		Model* model;
		int texIndex;

		glm::vec3 position;
		glm::vec3 origin;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 modelMatrix;
		bool modelUpdated = true;

		glm::vec2 texOffsetVector;

		float getTextureXOffset();
		float getTextureYOffset();

	public:
		Entity(Model* model,
			   glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f),
			   int texIndex = 0
		);
		virtual ~Entity();

		void setModel(Model* model);

		void changePosition(glm::vec3 position);
		void changeOrigin(glm::vec3 origin);
		void changeRotation(glm::vec3 rotation);
		void changeScale(glm::vec3 scale);
		
		void setPosition(glm::vec3 position);
		void setOrigin(glm::vec3 origin);
		void setRotation(glm::vec3 rotation);
		void setScale(glm::vec3 scale);

		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);

		void setRotationX(float x);
		void setRotationY(float y);
		void setRotationZ(float z);

		void updateModelMatrix();


		Model* getModel();

		glm::vec2 getTextureOffsetVector();

		glm::vec3 getPosition();
		glm::vec3 getOrigin();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		glm::mat4 getModelMatrix();
};
