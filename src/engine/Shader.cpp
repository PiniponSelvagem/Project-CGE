#pragma once
#include "Shader.h"

std::string Shader::loadShaderSource(const char* fileName) {
	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	// VERTEX
	in_file.open(fileName);

	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + "\n";
		}
	}
	else {
		std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << fileName << std::endl;
	}

	in_file.close();

	std::string version = std::to_string(glMajorVer) + std::to_string(glMinorVer) + "0";
	src.replace(src.find("#version"), 12, "#version " + version);

	return src;
}

GLuint Shader::loadShader(GLenum type, const char* fileName) {
	char infoLog[512];
	GLint success;

	GLuint shader = glCreateShader(type);
	std::string str_src = loadShaderSource(fileName);
	const GLchar* src = str_src.c_str();;
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << std::endl;
		std::cout << infoLog << std::endl;
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) {
	char infoLog[512];
	GLint success;

	id = glCreateProgram();

	glAttachShader(id, vertexShader);

	if (geometryShader) {
		glAttachShader(id, geometryShader);
	}

	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glUseProgram(0);
}




Shader::Shader(const int glMajorVer, const int glMinorVer, const char* vertexFile, const char* fragmentFile, const char* geometryFile)
	: glMajorVer(glMajorVer), glMinorVer(glMinorVer) {
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
	if (geometryFile != "") {
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
	}
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

	this->linkProgram(vertexShader, fragmentShader, geometryShader);


	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(id);
}


void Shader::set1i(GLint value, const GLchar* name) {
	use();
	glUniform1i(glGetUniformLocation(id, name), value);
	unuse();
}

void Shader::setVec1f(GLfloat value, const GLchar* name) {
	use();
	glUniform1f(glGetUniformLocation(id, name), value);
	unuse();
}
void Shader::setVec2f(glm::fvec2 value, const GLchar* name) {
	use();
	glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	unuse();
}
void Shader::setVec3f(glm::fvec3 value, const GLchar* name) {
	use();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	unuse();
}
void Shader::setVec4f(glm::fvec4 value, const GLchar* name) {
	use();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	unuse();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose) {
	use();
	glUniformMatrix3fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
	unuse();
}
void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose) {
	use();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
	unuse();
}