#include "sprites.h"
#include "packer/unpackThis.cc"

#pragma region PokeSprite
/*
    ______     _        _____            _ _       
    | ___ \   | |      /  ___|          (_) |      
    | |_/ /__ | | _____\ `--. _ __  _ __ _| |_ ___ 
    |  __/ _ \| |/ / _ \`--. \ '_ \| '__| | __/ _ \
    | | | (_) |   <  __/\__/ / |_) | |  | | ||  __/
    \_|  \___/|_|\_\___\____/| .__/|_|  |_|\__\___|
                            | |                   
                            |_|                   
*/
void PokeSprite::SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID){
  //Find Pokemon Name
  std::ifstream file("../assets/SpritesAnimated/pokedex.txt");
  if (!file.is_open()) return;

  std::string nombre;
  int i = 1;
  bool found = false;

  while (std::getline(file, nombre)) {
    if (i == pokeID) {
      found = true;
      break;
    }
    i++;
  }

  file.close();
  //Removing spaces ' '
  nombre.erase(std::remove(nombre.begin(), nombre.end(), ' '), nombre.end());

  if (!found) return;

  std::string isShiny = shiny ? " shiny" : "";
  std::string whichType;

  switch(type){
    case en_SpriteType::type_Attacker:{
      whichType = "Back";
      break;
    }
    case en_SpriteType::type_Defender:{
      whichType = "Front";
      break;
    }
    case en_SpriteType::type_Icon:{
      whichType = "Icons";
      break;
    }
  }

  char filesprite[75];
  char filedatabase[75];
  char fileindex[75];

  snprintf(filesprite, 75, "../assets/SpritesAnimated/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());
  snprintf(filedatabase, 75, "../assets/SpritesAnimated/%s%s/_sprites.dat", whichType.c_str(), isShiny.c_str());
  snprintf(fileindex, 75, "../assets/SpritesAnimated/%s%s/_index.txt", whichType.c_str(), isShiny.c_str());

  UnpackSprite(nombre.c_str(), fileindex, filedatabase);
  
  sprite = IMG_LoadTexture(sRenderer_, filesprite);
  SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);

  std::cout << "\nSprite Lodaded";
  std::cout << "\n" << nombre;
  std::cout << "\n" << filesprite;

  remove(filesprite);
  std::cout << "\nFile Ended";

  return;
}

void PokeSprite::InitSpriteSrc(bool tile){
  float w, h;
  SDL_GetTextureSize(sprite, &w, &h);

  if(tile){
    tileSize = h;
    numTiles = w / tileSize;

    src.x = 0;
    src.y = 0;
    src.w = tileSize;
    src.h = tileSize;
  }else{
    numTiles = 1;

    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;
  }
}

void PokeSprite::InitSpriteDst(float x, float y, float scale){
  if(sprite){
    dst.x = x;
    dst.y = y;

    SDL_GetTextureSize(sprite, &dst.w, &dst.h);
    dst.h *= scale;
    dst.w *= scale;
  }
}

void PokeSprite::InitPokemonSpriteDst(float x, float y, float scale){
  if(sprite){
    dst.x = x - (src.w / 2 * scale);;
    dst.y = y - (src.h * scale);

    dst.h = tileSize * scale;
    dst.w = tileSize * scale;
  }
}

void PokeSprite::UpdateSpriteDst(float x, float y, float scale){
  if(sprite){
    dst.x = x - (src.w / 2 * scale);
    dst.y = y - (src.h * scale);

    dst.h = tileSize * scale;
    dst.w = tileSize * scale;
  }
}

void PokeSprite::DrawSprite(){
  if(sprite){
    SDL_RenderTexture(sRenderer_, sprite, &src, &dst);
    DecideNextFrame();
  } 
}

void PokeSprite::ApplyFilter(float r, float g, float b){
  if(sprite) SDL_SetTextureColorMod(sprite, r, g, b);
}

void PokeSprite::DestroySprite(){
  if(sprite != NULL) SDL_DestroyTexture(sprite);     
}

void PokeSprite::DecideNextFrame(){
  Uint64 now = SDL_GetTicks();

  if (last == 0) last = now;

  if ((now - last) >= 120) {
    currentTile++;
    last = now;
  }

  src.x = src.h * (currentTile % numTiles);
}

PokeSprite::PokeSprite(SDL_Renderer* renderer){
  sRenderer_ = renderer;
}

PokeSprite::~PokeSprite(){
  DestroySprite();
}

#pragma region Sprite
/*
   _____            _ _       
  /  ___|          (_) |      
  \ `--. _ __  _ __ _| |_ ___ 
   `--. \ '_ \| '__| | __/ _ \
  /\__/ / |_) | |  | | ||  __/
  \____/| .__/|_|  |_|\__\___|
        | |                   
        |_|                   
*/

void Sprite::SelectSpriteFromRoute(const char* route){
  sprite = IMG_LoadTexture(sRenderer_, route);
}

void Sprite::InitSpriteSrc(bool tile){
  float w, h;
  SDL_GetTextureSize(sprite, &w, &h);

  if(tile){
    tileSize = h;
    numTiles = w / tileSize;

    src.x = 0;
    src.y = 0;
    src.w = tileSize;
    src.h = tileSize;
  }else{
    numTiles = 1;

    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;
  }
}

void Sprite::InitSpriteDst(float x, float y, float scale){
  if(sprite){
    dst.x = x;
    dst.y = y;

    SDL_GetTextureSize(sprite, &dst.w, &dst.h);
    dst.h *= scale;
    dst.w *= scale;
  }
}

void Sprite::UpdateSpriteDst(float x, float y, float scale){
  if(sprite){
    dst.x = x;
    dst.y = y;

    dst.h = tileSize * scale;
    dst.w = tileSize * scale;
  }
}

void Sprite::DrawSprite(){
  if(sprite){
    SDL_RenderTexture(sRenderer_, sprite, &src, &dst);
    DecideNextFrame();
  } 
}

void Sprite::ApplyFilter(float r, float g, float b){
  if(sprite) SDL_SetTextureColorMod(sprite, r, g, b);
}

void Sprite::DestroySprite(){
  if(sprite != NULL) SDL_DestroyTexture(sprite);     
}

void Sprite::DecideNextFrame(){
  if(numTiles > 1){
    Uint64 now = SDL_GetTicks();

    if (last == 0) last = now;

    if ((now - last) >= 120) {
      currentTile++;
      last = now;
    }

    src.x = src.h * (currentTile % numTiles);
  }
}

Sprite::Sprite(SDL_Renderer* renderer){
  sRenderer_ = renderer;
}

Sprite::~Sprite(){
  DestroySprite();
}