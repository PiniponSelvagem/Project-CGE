
class Texture {
	private:
		GLuint id;
		int width, height;
		unsigned int type;
		GLint textureUnit;

		void deleteTextureIfThisExists() {
			if (this->id) {
				glDeleteTextures(1, &this->id);
			}
		}
		

	public:
		Texture(const char* fileName, GLenum type, GLint textureUnit) {
			deleteTextureIfThisExists();

			this->type = type;
			this->textureUnit = textureUnit;

			loadTexture(fileName);
		}

		~Texture() {
			glDeleteTextures(1, &this->id);
		}

		inline GLuint getID() const {
			return this->id;
		}

		inline GLint getTextureUnit() const {
			return this->textureUnit;
		}

		void loadTexture(const char* fileName) {
			deleteTextureIfThisExists();

			/*				
			Jack42 - 1 ano atrás - 19:22
			If you actually you want to reuse the old texture, you should not delete it and create a new texture object,
			but only update the image with another call of glTexImage2D. Else I think a method loadFromFile would not make
			much sense if a new opengl texture object is created every time, then it would be more logical to just create
			multiple Texture instances by the constructor. 
			*/
			unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
			const char* soil_log = SOIL_last_result();

			glGenTextures(1, &this->id);
			glBindTexture(this->type, this->id);

			glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT); //S -> x axis
			glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT); //T -> y axis
			glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			if (image) {
				glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(this->type);
			}
			else {
				std::cout << "ERROR: [Texture] Failed to load texture " << fileName << ". " << soil_log << std::endl;
			}

			glActiveTexture(0);
			glBindTexture(this->type, 0);
			SOIL_free_image_data(image);
		}

		void bind() {
			glActiveTexture(GL_TEXTURE + this->textureUnit);
			glBindTexture(this->type, this->id);
		}

		void unbind() {
			glActiveTexture(0);
			glBindTexture(this->type, 0);
		}
};
