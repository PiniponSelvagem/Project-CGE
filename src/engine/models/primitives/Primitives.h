#pragma once

class Primitive {
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;


	public:
		Primitive();
		virtual ~Primitive();

		void set(const Vertex * vertices, const unsigned nVertices, const GLuint * indices, const unsigned nIndices);

		inline Vertex * getVertices() {
			return vertices.data();
		}

		inline GLuint * getIndices() {
			return indices.data();
		}

		inline const unsigned getNrVertices() {
			return vertices.size();
		}

		inline const unsigned getNrIndices() {
			return indices.size();
		}
};


class Triangle : public Primitive {
	public:
		Triangle() : Primitive();
};
class Quad : public Primitive {
	public:
		Quad() : Primitive() {
			Vertex vertices[] = {
				//Position							//Color							//Texcoords					//Normals				
				glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(-0.5f,-0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.5f,-0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
			};
			unsigned nVertices = sizeof(vertices) / sizeof(Vertex);

			GLuint indices[] = {
				0, 1, 2,	//Tri 1
				0, 2, 3,	//Tri 2
			};
			unsigned nIndices = sizeof(indices) / sizeof(GLuint);

			set(vertices, nVertices, indices, nIndices);
		}
};
class Cube : public Primitive {
	public:
		Cube() : Primitive() {
			Vertex vertices[] = {
				//Position							//Color							//Texcoords					//Normals	
				//FRONT
				///TRIG 1
				glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3( 0.f, 0.f, 1.f),  //0
				glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3( 0.f, 0.f, 1.f),  //1
				glm::vec3( 0.5f,-0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 0.f, 1.f),  //2
				///TRIG 2
				glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3( 0.f, 0.f, 1.f),  //0
				glm::vec3( 0.5f,-0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 0.f, 1.f),  //2
				glm::vec3( 0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3( 0.f, 0.f, 1.f),  //3

				//RIGHT
				///TRIG 1
				glm::vec3( 0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 1.f),		glm::vec3( 1.f, 0.f, 0.f),  //3
				glm::vec3( 0.5f,-0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3( 1.f, 0.f, 0.f),  //2
				glm::vec3( 0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3( 1.f, 0.f, 0.f),  //7
				///TRIG 2
				glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 1.f),		glm::vec3( 1.f, 0.f, 0.f),  //3
				glm::vec3(0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3( 1.f, 0.f, 0.f),  //7
				glm::vec3(0.5f, 0.5f,-0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f), 		glm::vec3( 1.f, 0.f, 0.f),  //4
				
				//BACK
				///TRIG 1
				glm::vec3( 0.5f, 0.5f,-0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3( 0.f, 0.f,-1.f),  //4
				glm::vec3( 0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3( 0.f, 0.f,-1.f),  //7
				glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 0.f,-1.f),  //6
				///TRIG 2
				glm::vec3( 0.5f, 0.5f,-0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f), 		glm::vec3( 0.f, 0.f,-1.f),  //4
				glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 0.f,-1.f),  //6
				glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3( 0.f, 0.f,-1.f),  //5

				//LEFT
				///TRIG 1
				glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),  //5
				glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),  //6
				glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),  //1
				///TRIG 2
				glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),  //5
				glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),  //1
				glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f), 		glm::vec3(-1.f, 0.f, 0.f),  //0

				//TOP
				///TRIG 1
				glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3( 0.f, 1.f, 0.f),  //5
				glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 0.f), 		glm::vec3( 0.f, 1.f, 0.f),  //0
				glm::vec3( 0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 1.f, 0.f),  //3
				///TRIG 2
				glm::vec3(-0.5f, 0.5f,-0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3( 0.f, 1.f, 0.f),  //5
				glm::vec3( 0.5f, 0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3( 0.f, 1.f, 0.f),  //3
				glm::vec3( 0.5f, 0.5f,-0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f), 		glm::vec3( 0.f, 1.f, 0.f),  //4

				//BOTTOM
				///TRIG 1
				glm::vec3( 0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f,-1.f, 0.f),  //7
				glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f,-1.f, 0.f),  //1
				glm::vec3(-0.5f,-0.5f,-0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f,-1.f, 0.f),  //6
				///TRIG 2
				glm::vec3( 0.5f,-0.5f,-0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f,-1.f, 0.f),  //7
				glm::vec3( 0.5f,-0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f,-1.f, 0.f),  //2
				glm::vec3(-0.5f,-0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f,-1.f, 0.f),  //1
			};
			unsigned nVertices = sizeof(vertices) / sizeof(Vertex);

			set(vertices, nVertices, nullptr, 0);
		}
};