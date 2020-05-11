#pragma once
#include "Shader.h"

std::string Shader::loadShaderSource(const char* fileName) {
	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

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

	return src;
}

GLuint Shader::loadShader(const char* fileName, GLenum type) {
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
		std::cerr << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << fileName << std::endl;
		std::cerr << infoLog << std::endl;
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
	char infoLog[512];
	GLint success;

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;
		std::cerr << infoLog << std::endl;
	}

	glUseProgram(0);
}

void Shader::load() {
	vertexShaderID   = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	this->linkProgram(vertexShaderID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::unload() {
	unuse();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteProgram(programID);
}




Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	this->vertexFile = vertexFile;
	this->fragmentFile = fragmentFile;

	load();
}

Shader::~Shader() {
	unload();
}

void Shader::reload() {
	unload();
	load();
}

void Shader::set1i(GLint value, const GLchar* name) {
	glUniform1i(glGetUniformLocation(programID, name), value);
}

void Shader::set1f(GLfloat value, const GLchar* name) {
	glUniform1f(glGetUniformLocation(programID, name), value);
}
void Shader::setVec2f(glm::fvec2 value, const GLchar* name) {
	glUniform2fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(value));
}
void Shader::setVec3f(glm::fvec3 value, const GLchar* name) {
	glUniform3fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(value));
}
void Shader::setVec4f(glm::fvec4 value, const GLchar* name) {
	glUniform3fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(value));
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose) {
	glUniformMatrix3fv(glGetUniformLocation(programID, name), 1, transpose, glm::value_ptr(value));
}
void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose) {
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, transpose, glm::value_ptr(value));
}