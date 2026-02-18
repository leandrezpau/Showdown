#include "sprites.h"
#include "packer/unpackThis.cc"

#pragma region BaseSprite

SDL_Renderer* BaseSprite::sRenderer_ = nullptr;

void BaseSprite::SetSpritesRenderer(SDL_Renderer* renderer){
  sRenderer_ = renderer;
}

void BaseSprite::InitSpriteSrc(bool tile){
  float w, h;
  SDL_GetTextureSize(sprite, &w, &h);

  if(tile){
    tileSize = (short int) h;
    numTiles = (short int) w / tileSize;

    src = {0, 0, (float)tileSize, (float)tileSize};
  }else{
    numTiles = 1;
    src = {0, 0, w, h};
  }
}

void BaseSprite::InitSpriteDst(float x, float y, float scale, bool centered){
  if(!sprite) return;

  if(centered){
    dst.x = x - (src.w / 2 * scale);
    dst.y = y - (src.h / 2 * scale);
  }else{
    dst.x = x;
    dst.y = y;
  }

  dst.w = src.w * scale;
  dst.h = src.h * scale;
}

void BaseSprite::UpdateSpriteDst(float x, float y, float scale, bool centered){
  InitSpriteDst(x, y, scale, centered);
}

void BaseSprite::DrawSprite(int frameDelay){
  if(!sprite) return;

  SDL_RenderTexture(sRenderer_, sprite, &src, &dst);

  if(numTiles > 1){
    Uint64 now = SDL_GetTicks();

    if(last == 0) last = now;

    if((now - last) >= frameDelay){
      currentTile++;
      last = now;
    }

    src.x = src.h * (currentTile % numTiles);
  }
}

void BaseSprite::ApplyFilter(float r, float g, float b){
  if(sprite) SDL_SetTextureColorMod(sprite, (Uint8) r, (Uint8) g, (Uint8) b);
}

void BaseSprite::DestroySprite(){
  if(sprite){
    SDL_DestroyTexture(sprite);
    sprite = nullptr;
  }
}

BaseSprite::~BaseSprite(){
  DestroySprite();
}

#pragma region Sprite
// SPRITE
void Sprite::SelectSpriteFromRoute(const char* route){
  sprite = IMG_LoadTexture(sRenderer_, route);
  SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
}


#pragma region PokeSprite
// POKE_SPRITE
void PokeSprite::SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID){

  std::ifstream file("../assets/SpritesAnimated/pokedex.txt");
  if(!file.is_open()) return;

  std::string nombre;
  int i = 1;
  while(std::getline(file, nombre)){
    if(i++ == pokeID) break;
  }
  file.close();

  nombre.erase(std::remove(nombre.begin(), nombre.end(), ' '), nombre.end());
  nombre.erase(std::remove(nombre.begin(), nombre.end(), '-'), nombre.end());

  std::string isShiny = shiny ? " shiny" : "";
  std::string whichType;

  switch(type){
    case type_Attacker: whichType = "Back"; break;
    case type_Defender: whichType = "Front"; break;
    case type_Icon:     whichType = "Icons"; break;
  }

  char filesprite[128];
  char filedatabase[128];
  char fileindex[128];

  snprintf(filesprite, 128, "../assets/SpritesAnimated/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());
  snprintf(filedatabase, 128, "../assets/SpritesAnimated/%s%s/_sprites.dat", whichType.c_str(), isShiny.c_str());
  snprintf(fileindex, 128, "../assets/SpritesAnimated/%s%s/_index.txt", whichType.c_str(), isShiny.c_str());

  UnpackSprite(nombre.c_str(), fileindex, filedatabase);

  sprite = IMG_LoadTexture(sRenderer_, filesprite);
  SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);

  remove(filesprite);
}