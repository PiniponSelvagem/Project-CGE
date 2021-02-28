#pragma once
#include <engine/terrains/TerrainTexturePack.h>

TerrainTexturePack::TerrainTexturePack(Texture* backTex, Texture* backTexSpecular,
					Texture* rTex, Texture* rTexSpecular,
					Texture* gTex, Texture* gTexSpecular,
					Texture* bTex, Texture* bTexSpecular)
	: backTex(backTex), backTexSpecular(backTexSpecular),
	rTex(rTex), rTexSpecular(rTexSpecular),
	gTex(gTex), gTexSpecular(gTexSpecular),
	bTex(bTex), bTexSpecular(bTexSpecular) { }
TerrainTexturePack::~TerrainTexturePack() { }

Texture* TerrainTexturePack::getBackTex() { return backTex; }
Texture* TerrainTexturePack::getRTex() { return rTex; }
Texture* TerrainTexturePack::getGTex() { return gTex; }
Texture* TerrainTexturePack::getBTex() { return bTex; }

Texture* TerrainTexturePack::getBackTexSpecular() { return backTexSpecular; }
Texture* TerrainTexturePack::getRTexSpecular() { return rTexSpecular; }
Texture* TerrainTexturePack::getGTexSpecular() { return gTexSpecular; }
Texture* TerrainTexturePack::getBTexSpecular() { return bTexSpecular; }