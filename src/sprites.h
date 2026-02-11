#pragma once

#define _SPRITES_H_
#ifdef _SPRITES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Sprite {
public: 
	enum en_SpriteType{
		type_Attacker = 0,
		type_Defender,
		type_Icon,
	};
	static const int kNPokes = 721;

	en_SpriteType typeSprite;

	SDL_Texture* sprite; //Where to load sprite
	SDL_FRect dst; // x, y, w (width), h (height)
	SDL_FRect src; // x, y, w (width), h (height)

	short int numTiles;
	short int currentTile = 0;
	short int tileSize;

	Uint64 last = 0;

	SDL_Renderer* renderer_; //Same renderer as window
	

	void SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID);
	void SelectSpriteFromRoute(const char* route);

	void InitSpriteDst(float x, float y, float scale);
	void InitPokemonSpriteDst(float x, float y, float scale);
	void UpdateSpriteDst(float x, float y, float scale);
	
	void InitSpriteSrc(bool tile = true);
	
	
	

	void DecideNextFrame();

	void DrawSprite();
	void ApplyFilter(float r, float g, float b);

	void DestroySprite();

	Sprite(SDL_Renderer* renderer);
	~Sprite();
};

#endif //_SPRITES_H_