#pragma once
#include "../models/Texture.h"

class TerrainTexturePack {
	private:
		Texture* backgroundTex;
		Texture* rTex;
		Texture* gTex;
		Texture* bTex;

	public:
		TerrainTexturePack(Texture* backgroundTex,
						   Texture* rTex,
						   Texture* gTex,
						   Texture* bTex) 
		: backgroundTex(backgroundTex), rTex(rTex), gTex(gTex), bTex(bTex)
		{ }
		virtual ~TerrainTexturePack() { }

		inline Texture* getBackgroundTex() const { return backgroundTex; }
		inline Texture* getRTex() const { return rTex; }
		inline Texture* getGTex() const { return gTex; }
		inline Texture* getBTex() const { return bTex; }
};