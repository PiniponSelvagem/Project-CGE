#pragma once
#include "../../../libs.h"
#include "Model.h"

class Entity {
	private:
		Model* model;

		glm::vec3 position;
		glm::vec3 origin;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 modelMatrix;


	public:
		Entity(Model* model, glm::vec3 position, glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f))
			: model(model), position(position), origin(origin), rotation(rotation), scale(scale)
		{ }

		inline void setModel(Model* model) { this->model = model; }

		inline void changePosition(glm::vec3 position) { this->position += position; }
		inline void changeOrigin(glm::vec3 origin)     { this->origin += origin; }
		inline void changeRotation(glm::vec3 rotation) { this->rotation += rotation; }
		inline void changeScale(glm::vec3 scale)       { this->scale += scale; }
		
		inline void setPosition(glm::vec3 position) { this->position = position; }
		inline void setOrigin(glm::vec3 position)   { this->origin = origin; }
		inline void setRotation(glm::vec3 rotation) { this->rotation = rotation; }
		inline void setScale(glm::vec3 scale)       { this->scale = scale; }

		void updateModelMatrix();


		inline Model* getModel() const { return model; }

		inline glm::vec3 getPosition() const { return position; }
		inline glm::vec3 getOrigin() const   { return origin; }
		inline glm::vec3 getRotation() const { return rotation; }
		inline glm::vec3 getScale() const    { return scale; }

		inline glm::mat4 getModelMatrix() const { return modelMatrix; }
};
