#pragma once
#include <engine/models/Texture.h>

void Texture::load(const char* fileName) {
	/*
	Jack42 - 1 ano atr�s - 19:22
	If you actually you want to reuse the old texture, you should not delete it and create a new texture object,
	but only update the image with another call of glTexImage2D. Else I think a method loadFromFile would not make
	much sense if a new opengl texture object is created every time, then it would be more logical to just create
	multiple Texture instances by the constructor.
	*/

	unsigned char* image = SOIL_load_image(fileName, &width, &height, NULL, SOIL_LOAD_RGBA);
	const char* soil_log = SOIL_last_result();

	glGenTextures(1, &id);
	glBindTexture(type, id);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT); //S -> x axis
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT); //T -> y axis

	//Texture Filtering
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (image) {
		glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(type);
		//TODO: Possible graphical setting
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(type, GL_TEXTURE_LOD_BIAS, -1);
	}
	else {
		std::cout << "ERROR::TEXTURE::LOAD: Failed to load texture " << fileName << ". " << soil_log << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(type, 0);
	SOIL_free_image_data(image);
}



Texture::Texture(const char* fileName, GLenum type, int nOfRows) {
	this->type = type;
	this->nOfRows = nOfRows;
	load(fileName);
}
Texture::~Texture() {
	glDeleteTextures(1, &id);
}

GLuint Texture::getID()   { return id;      }
int Texture::getType()    { return type;    }
int Texture::getNOfRows() { return nOfRows; }

int Texture::getWidth()  { return width;  }
int Texture::getHeight() { return height; }