#pragma once

#define _SPRITES_H_
#ifdef _SPRITES_H_

#include <stdint.h>

class Sprite{
public:
	static const int kNPokes = 721;

	struct SpriteIndex{									//Struct to store sprites while init
		int id;
		int32_t offset;
		int32_t size;
	};

	int ExtractSprite(int kNPokemons);
	void DeleteAllSprites();
};



#endif //_SPRITES_H_