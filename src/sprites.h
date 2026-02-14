#pragma once

#define _SPRITES_H_
#ifdef _SPRITES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

enum en_SpriteType{
	type_Attacker = 0,
	type_Defender,
	type_Icon,
};

class PokeSprite {
public: 
	static const int kNPokes = 721;

	en_SpriteType typeSprite;		// Type of sprite is been used -> Back, Front or Icon

	SDL_Texture* sprite; 				// Where to load sprite
	SDL_FRect dst; 							// x, y, w, h (of the sprite)
	SDL_FRect src; 							// x, y, w, h (of the tile used in sprite)

	short int numTiles;					// Num of tiles sprite has
	short int currentTile = 0;	// Current Tile is been used
	short int tileSize;					// As sprites are rectangular (a lot of square tiles)
	                            // And every tile is a square, used as pixel size of it

	Uint64 last = 0;						// Timer for selecting next tile

	SDL_Renderer* sRenderer_; 	// Renderer of the window (getted by constructor directly from main.cc)
	

	void SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID);

	void InitPokemonSpriteDst(float x, float y, float scale);
	void UpdatePokemonSpriteDst(float x, float y, float scale);
	
	void InitSpriteSrc(bool tile = true);
	
	void DecideNextFrame();

	void DrawSprite();
	void ApplyFilter(float r, float g, float b);

	void DestroySprite();

	PokeSprite(SDL_Renderer* renderer);
	~PokeSprite();
};

class Sprite {
public: 
	static const int kNPokes = 721;

	en_SpriteType typeSprite;		// Type of sprite is been used -> Back, Front or Icon

	SDL_Texture* sprite; 				// Where to load sprite
	SDL_FRect dst; 							// x, y, w, h (of the sprite)
	SDL_FRect src; 							// x, y, w, h (of the tile used in sprite)

	short int numTiles;					// Num of tiles sprite has
	short int currentTile = 0;	// Current Tile is been used
	short int tileSize;					// As sprites are rectangular (a lot of square tiles)
	                            // And every tile is a square, used as pixel size of it

	Uint64 last = 0;						// Timer for selecting next tile

	SDL_Renderer* sRenderer_; 	// Renderer of the window (getted by constructor directly from main.cc)
	
	void SelectSpriteFromRoute(const char* route);

	void InitSpriteDst(float x, float y, float scale);
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