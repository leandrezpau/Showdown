#include "sprites.h"
#include "packer/unpackThis.cc"

void Sprite::SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID){
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

    if (!found) return;
    std::string isShiny = shiny ? "" : " shiny";
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
    char filesprite[50];
    char filedatabase[50];
    char fileindex[50];
    snprintf(filesprite, 50, "../assets/SpritesAnimated/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());
    snprintf(filedatabase, 50, "../assets/SpritesAnimated/%s%s/_sprites.dat", whichType.c_str(), isShiny.c_str());
    snprintf(fileindex, 50, "../assets/SpritesAnimated/%s%s/_index.txt", whichType.c_str(), isShiny.c_str());

    UnpackSprite(nombre.c_str(), fileindex, filedatabase);
    
    sprite = IMG_LoadTexture(renderer_, filesprite);
    SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
    std::cout << "\nSprite Lodaded";
    std::cout << "\n" << nombre;
    std::cout << "\n" << filesprite;

    remove(filesprite);
    std::cout << "\nFile Ended";
    
    
    return;
}
void Sprite::SelectSpriteFromRoute(const char* route){
    sprite = IMG_LoadTexture(renderer_, route);
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
void Sprite::InitPokemonSpriteDst(float x, float y, float scale){
    if(sprite){
        dst.x = x;
        dst.y = y;

        dst.h = tileSize * scale;
        dst.w = tileSize * scale;
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
        SDL_RenderTexture(renderer_, sprite, &src, &dst);
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
  Uint64 now = SDL_GetTicks();

  if (last == 0) last = now;

  if ((now - last) >= 120) {
    currentTile++;
    last = now;
  }

  src.x = src.h * (currentTile % numTiles);
}

Sprite::Sprite(SDL_Renderer* renderer){
    renderer_ = renderer;
}

Sprite::~Sprite(){
    DestroySprite();
}