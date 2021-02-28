#pragma once
#include <engine/models/Texture.h>

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
						   Texture* bTex, Texture* bTexSpecular);
		virtual ~TerrainTexturePack();

		Texture* getBackTex();
		Texture* getRTex();
		Texture* getGTex();
		Texture* getBTex();

		Texture* getBackTexSpecular();
		Texture* getRTexSpecular();
		Texture* getGTexSpecular();
		Texture* getBTexSpecular();
};