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

		inline void bind(const GLint textureUnit) {
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(type, id);
		}
		inline void unbind() {
			glActiveTexture(0);
			glBindTexture(type, 0);
		}
};
