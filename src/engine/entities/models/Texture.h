#pragma once
#include "../../../libs.h"

class Texture {
	private:
		GLuint id;
		int type;

		void load(const char* fileName);


	public:
		Texture(const char* fileName, GLenum type);
		virtual ~Texture();

		inline GLuint getID() const { return id; }
		inline int getType() const  { return type; }
};
