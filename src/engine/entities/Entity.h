#pragma once
#include "../../libs.h"
#include "../models/Model.h"

class Entity {
	private:
		Model* model;

		glm::vec3 position;
		glm::vec3 origin;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 modelMatrix;
		bool modelUpdated = true;

	public:
		Entity(Model* model, glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
			: model(model), position(position), origin(origin), rotation(rotation), scale(scale)
		{ }
		virtual ~Entity() { }

		inline void setModel(Model* model) { this->model = model; }

		inline void changePosition(glm::vec3 position) { this->position += position; modelUpdated = true; }
		inline void changeOrigin(glm::vec3 origin)     { this->origin += origin;     modelUpdated = true; }
		inline void changeRotation(glm::vec3 rotation) { this->rotation += rotation; modelUpdated = true; }
		inline void changeScale(glm::vec3 scale)       { this->scale += scale;       modelUpdated = true; }
		
		inline void setPosition(glm::vec3 position) { this->position = position; modelUpdated = true; }
		inline void setOrigin(glm::vec3 origin)     { this->origin = origin;     modelUpdated = true; }
		inline void setRotation(glm::vec3 rotation) { this->rotation = rotation; modelUpdated = true; }
		inline void setScale(glm::vec3 scale)       { this->scale = scale;       modelUpdated = true; }

		void updateModelMatrix();


		inline Model* getModel() { return model; }

		inline glm::vec3 getPosition() { return position; }
		inline glm::vec3 getOrigin()   { return origin; }
		inline glm::vec3 getRotation() { return rotation; }
		inline glm::vec3 getScale()    { return scale; }

		inline glm::mat4 getModelMatrix() { return modelMatrix; }
};
