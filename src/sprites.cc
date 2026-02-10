#include "sprites.h"

void Sprite::SelectSprite(SDL_Renderer* renderer, bool shiny, en_SpriteType type, int pokeID){
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
    }
    char filesprite[50];
    snprintf(filesprite, 50, "../assets/SpritesPokemon/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());

    s = IMG_LoadTexture(renderer, filesprite);

    std::cout << "\nSprite Lodaded";
    std::cout << "\n" << nombre;
    std::cout << "\n" << filesprite;
    return;   // no encontrado
}

void Sprite::SelectDst(en_SpriteType type, float x, float y){
    dst.x = x;
    dst.y = y;

    if(type == en_SpriteType::type_Attacker){
        dst.h = 160;
        dst.w = 160;
    }else{
        dst.h = 192;
        dst.w = 192;
    }
}