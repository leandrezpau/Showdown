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

#include "textureManager.h"

enum en_SpriteType{
	type_Attacker = 0,
	type_Defender,
	type_Icon,
};

class BaseSprite {
protected:
	static const int kNPokes = 721;

  int textureID;

  std::vector<SDL_FRect> src{};
  std::vector<SDL_FRect> dst{};
  

  static short int spriteIndexer;
  short int numTiles = 1;
  short int currentTile = 0;
  short int tileSize = 0;

  Uint64 last = 0;

  static SDL_Renderer* sRenderer_;

public:
  static void SetSpritesRenderer(SDL_Renderer* renderer);

  void InitSpriteSrc(bool tile = true, float x = 0, float y = 0, float w = 0, float h = 0);
  void InitSpriteDst(float x, float y, float scale, bool centered = false, int index = 0, float w = 0, float h = 0);
  void UpdateSpriteDst(float x, float y, float scale, bool centered = false, int index = 0);

  void DrawSprite(SDL_FRect dst_, int frameDelay = 150, int index = 0);
  void ApplyFilter(float r, float g, float b);
  void SetTextureID();

  //Getters
  SDL_FRect GetDst();

  //Setters

  virtual ~BaseSprite();
};

class Sprite : public BaseSprite {
public:
  void SelectSpriteFromRoute(const char* route);
};

class PokeSprite : public BaseSprite {
public:
  en_SpriteType typeSprite;		// Type of sprite is been used -> Back, Front or Icon
  void SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID);
};

#endif //_SPRITES_H_