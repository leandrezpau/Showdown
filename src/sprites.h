#pragma once

#define _SPRITES_H_
#ifdef _SPRITES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Sprite {
public: 
	enum en_SpriteType{
		type_Attacker = 0,
		type_Defender,
	};
	static const int kNPokes = 721;

	SDL_Texture* s; //Where to load sprite

	SDL_FRect dst; // x, y, w (width), h (height)

	void SelectSprite(SDL_Renderer* renderer, bool shiny, en_SpriteType type, int pokeID);
	void SelectDst(en_SpriteType type, float x, float y);
};

#endif //_SPRITES_H_