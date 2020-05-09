#pragma once

/* glDrawArrays */
/*
struct Vertex {
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::vec3 color;
};
*/

/* glDrawElements (position in other VBO) */
struct VertexData {
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::vec3 color;
};