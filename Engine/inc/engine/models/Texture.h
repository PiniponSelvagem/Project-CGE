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

		inline GLuint getID()	{ return id; }
		inline int getType()	{ return type; }
		inline int getNOfRows() { return nOfRows; }

		inline int getWidth()	{ return width; }
		inline int getHeight()	{ return height; }
};
