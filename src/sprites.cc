#include "sprites.h"

void Sprite::SelectSprite(bool shiny, en_SpriteType type, int pokeID){
    //Find Pokemon Name
    std::ifstream file("../assets/SpritesPokemon/pokedex.txt");
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
    snprintf(filesprite, 50, "../assets/SpritesAnimated/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());

    
    sprite = IMG_LoadTexture(renderer_, filesprite);
    SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);

    std::cout << "\nSprite Lodaded";
    std::cout << "\n" << nombre;
    std::cout << "\n" << filesprite;
    return;
}

void Sprite::InitSpriteSrc(){
    float w, h;
    SDL_GetTextureSize(sprite, &w, &h);
    
    tileSize = h;

    numTiles = w / tileSize;

    src.x = 0;
    src.y = 0;
    src.w = tileSize;
    src.h = tileSize;
}

void Sprite::InitSpriteDst(en_SpriteType type, float x, float y){
    if(sprite){
        dst.x = x;
        dst.y = y;
        switch(type){
            case en_SpriteType::type_Attacker:{
                dst.h = tileSize * 3;
                dst.w = tileSize * 3;
                break;
            }
            case en_SpriteType::type_Defender:{
                dst.h = tileSize * 3;
                dst.w = tileSize * 3;
                break;
            }
            case en_SpriteType::type_Icon:{
                dst.h = 128;
                dst.w = 64;
                break;
            }
        }
    }
}
void Sprite::UpdateSpriteDst(en_SpriteType type, float x, float y){
    if(sprite){
        dst.x = x;
        dst.y = y;
        switch(type){
            case en_SpriteType::type_Attacker:{
                dst.h = src.h * 3;
                dst.w = src.h * 3;
                break;
            }
            case en_SpriteType::type_Defender:{
                dst.h = src.h * 3;
                dst.w = src.h * 3;
                break;
            }
            case en_SpriteType::type_Icon:{
                dst.h = 128;
                dst.w = 64;
                break;
            }
        }
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