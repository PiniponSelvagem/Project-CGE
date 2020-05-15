#pragma once
#include "../models/Texture.h"

class TerrainTexturePack {
	private:
		Texture* backTex, *backTexSpecular;
		Texture* rTex,	  *rTexSpecular;
		Texture* gTex,	  *gTexSpecular;
		Texture* bTex,	  *bTexSpecular;

	public:
		TerrainTexturePack(Texture* backTex, Texture* backTexSpecular,
						   Texture* rTex, Texture* rTexSpecular,
						   Texture* gTex, Texture* gTexSpecular,
						   Texture* bTex, Texture* bTexSpecular)
		: backTex(backTex), backTexSpecular(backTexSpecular),
			rTex(rTex), rTexSpecular(rTexSpecular),
			gTex(gTex), gTexSpecular(gTexSpecular),
			bTex(bTex), bTexSpecular(bTexSpecular)
		{ }
		virtual ~TerrainTexturePack() { }

		inline Texture* getBackTex() const { return backTex; }
		inline Texture* getRTex() const { return rTex; }
		inline Texture* getGTex() const { return gTex; }
		inline Texture* getBTex() const { return bTex; }

		inline Texture* getBackTexSpecular() const { return backTexSpecular; }
		inline Texture* getRTexSpecular() const { return rTexSpecular; }
		inline Texture* getGTexSpecular() const { return gTexSpecular; }
		inline Texture* getBTexSpecular() const { return bTexSpecular; }
};