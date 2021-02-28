#pragma once
#include <engine/Libs.h>

class Texture {
	private:
		GLuint id;
		int type;
		int nOfRows;
		int width, height;

		void load(const char* fileName);


	public:
		Texture(const char* fileName, GLenum type, int nOfRows = 1);
		virtual ~Texture();

		GLuint getID();
		int getType();
		int getNOfRows();

		int getWidth();
		int getHeight();
};
