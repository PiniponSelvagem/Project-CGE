#pragma once
#include "../../libs.h"
#include "../models/Model.h"

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

	public:
		Entity(Model* model,
			glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f),
			int texIndex = 0
		)
			: model(model), position(position), origin(origin), rotation(rotation), scale(scale), texIndex(texIndex)
		{ }
		virtual ~Entity() { }

		inline void setModel(Model* model) { this->model = model; }

		inline void changePosition(glm::vec3 position) { this->position += position; modelUpdated = true; }
		inline void changeOrigin(glm::vec3 origin)     { this->origin += origin;     modelUpdated = true; }
		inline void changeRotation(glm::vec3 rotation) {
			this->rotation += rotation;
			modelUpdated = true;

			if (this->rotation.x > 360.f || this->rotation.x < -360.f) this->rotation.x = 0.f;
			if (this->rotation.y > 360.f || this->rotation.y < -360.f) this->rotation.y = 0.f;
			if (this->rotation.z > 360.f || this->rotation.z < -360.f) this->rotation.z = 0.f;
		}
		inline void changeScale(glm::vec3 scale)       { this->scale += scale;       modelUpdated = true; }
		
		inline void setPosition(glm::vec3 position) { this->position = position; modelUpdated = true; }
		inline void setOrigin(glm::vec3 origin)     { this->origin = origin;     modelUpdated = true; }
		inline void setRotation(glm::vec3 rotation) { this->rotation = rotation; modelUpdated = true; }
		inline void setScale(glm::vec3 scale)       { this->scale = scale;       modelUpdated = true; }

		inline void setPositionX(float x) { this->position.x = x; modelUpdated = true; }
		inline void setPositionY(float y) { this->position.y = y; modelUpdated = true; }
		inline void setPositionZ(float z) { this->position.z = z; modelUpdated = true; }

		inline void setRotationX(float x) { this->rotation.x = x; modelUpdated = true; }
		inline void setRotationY(float y) { this->rotation.y = y; modelUpdated = true; }
		inline void setRotationZ(float z) { this->rotation.z = z; modelUpdated = true; }

		void updateModelMatrix();


		inline Model* getModel() { return model; }
		inline float getTextureXOffset() {
			int nOfRows = model->getDiffuseTex()->getNOfRows();
			int column = texIndex % nOfRows;
			return column / nOfRows;
		}
		inline float getTextureYOffset() {
			int nOfRows = model->getDiffuseTex()->getNOfRows();
			int row = texIndex / nOfRows;
			return row / nOfRows;
		}

		inline glm::vec3 getPosition() { return position; }
		inline glm::vec3 getOrigin()   { return origin; }
		inline glm::vec3 getRotation() { return rotation; }
		inline glm::vec3 getScale()    { return scale; }

		inline glm::mat4 getModelMatrix() { return modelMatrix; }
};
