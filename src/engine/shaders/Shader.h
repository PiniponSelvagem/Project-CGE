#pragma once
#include "../../libs.h"

class Shader {
	private:
		const char* vertexFile;
		const char* fragmentFile;
		const char* geometryFile;

		GLuint id;

		std::string loadShaderSource(const char* fileName);

		GLuint loadShader(GLenum type, const char* fileName);

		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

	public:
		Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");

		~Shader();

		void reload();

		// Set uniform functions
		inline void use() {
			glUseProgram(id);
		}
		inline void unuse() {
			glUseProgram(0);
		}


		void set1i(GLint value, const GLchar* name);

		void setVec1f(GLfloat value, const GLchar* name);
		void setVec2f(glm::fvec2 value, const GLchar* name);
		void setVec3f(glm::fvec3 value, const GLchar* name);
		void setVec4f(glm::fvec4 value, const GLchar* name);

		void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
		void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
};