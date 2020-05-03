#pragma once
#include "../../libs.h"

class Shader {
	private:
		const char* vertexFile;
		const char* fragmentFile;

		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		std::string loadShaderSource(const char* fileName);

		GLuint loadShader(const char* fileName, GLenum type);

		void linkProgram(GLuint vertexShader, GLuint fragmentShader);

		void load();
		void unload();

	public:
		Shader(const char* vertexFile, const char* fragmentFile);
		virtual ~Shader();

		void reload();

		inline void use() {	glUseProgram(programID); }
		inline void unuse() { glUseProgram(0); }


		void set1i(GLint value, const GLchar* name);
		void set1f(GLfloat value, const GLchar* name);

		void setVec2f(glm::fvec2 value, const GLchar* name);
		void setVec3f(glm::fvec3 value, const GLchar* name);
		void setVec4f(glm::fvec4 value, const GLchar* name);

		void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
		void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
};