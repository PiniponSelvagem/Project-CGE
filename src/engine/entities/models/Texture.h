#pragma once
#include "../../../libs.h"

class Texture {
	private:
		GLuint id;
		int width, height;
		unsigned int type;

		void deleteTextureIfThisExists();
		

	public:
		Texture(const char* fileName, GLenum type);
		~Texture();

		inline GLuint getID() const {
			return id;
		}

		void loadTexture(const char* fileName);

		void bind(const GLint textureUnit);
		void unbind();
};
