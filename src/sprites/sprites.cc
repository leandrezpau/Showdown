#include "sprites.h"
#include "../packer/unpackThis.cc"

#pragma region BaseSprite

// Static member initialization for the SDL renderer
SDL_Renderer* BaseSprite::sRenderer_ = nullptr;
short int BaseSprite::spriteIndexer = 0;
/**
 * Sets the global renderer to be used by all sprite instances.
 */
void BaseSprite::SetSpritesRenderer(SDL_Renderer* renderer){
  sRenderer_ = renderer;
}

/**
 * Initializes the source rectangle (src) from the loaded texture.
 * If 'tile' is true, it assumes a horizontal spritesheet where each frame is square.
 */
void BaseSprite::InitSpriteSrc(bool tile){
  if(TextureManager::Get(textureID) == nullptr) return;
  
  float w, h;
  SDL_GetTextureSize(TextureManager::Get(textureID), &w, &h);
  
  if(TextureManager::Get(textureID) != nullptr){
    if(tile){
      // For animated tiles, the height determines the size of the square frame
      tileSize = (short int) h;
      numTiles = (short int) w / tileSize;
      src = {0, 0, (float)tileSize, (float)tileSize};
    }else{
      // Static sprite: the source is the entire texture
      numTiles = 1;
      src = {0, 0, w, h};
    }
  }
}

/**
 * Defines the destination rectangle on the screen.
 * Can center the sprite based on the provided x and y coordinates.
 */
void BaseSprite::InitSpriteDst(float x, float y, float scale, bool centered){
  if(TextureManager::Get(textureID) == nullptr) return;

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

/**
 * Wrapper to update the sprite's position and scale on the screen.
 */
void BaseSprite::UpdateSpriteDst(float x, float y, float scale, bool centered){
  InitSpriteDst(x, y, scale, centered);
}

/**
 * Renders the sprite to the screen and manages frame animation timing.
 */
void BaseSprite::DrawSprite(int frameDelay){
  if(TextureManager::Get(textureID) == nullptr) return;

  SDL_RenderTexture(sRenderer_, TextureManager::Get(textureID), &src, &dst);

  // If the sprite is an animation (multiple tiles)
  if(numTiles > 1){
    Uint64 now = SDL_GetTicks();

    if(last == 0) last = now;

    // Advance to the next frame if the delay time has passed
    if((now - last) >= frameDelay){
      currentTile++;
      last = now;
    }

    // Move the source rectangle to the current frame index
    src.x = src.h * (currentTile % numTiles);
  }
}

/**
 * Changes the color modulation of the texture (RGB filtering).
 */
void BaseSprite::ApplyFilter(float r, float g, float b){
  if(TextureManager::Get(textureID) != nullptr) 
    SDL_SetTextureColorMod(TextureManager::Get(textureID), (Uint8) r, (Uint8) g, (Uint8) b);
}

void BaseSprite::SetTextureID(int id){
  textureID = id;
}

BaseSprite::~BaseSprite(){
}

#pragma region Sprite

/**
 * Standard Sprite: Loads a texture directly from a file path.
 */
void Sprite::SelectSpriteFromRoute(const char* route){
  TextureManager::Load(sRenderer_, textureID, route);
}

#pragma region PokeSprite

/**
 * Specialized Pokémon Sprite: 
 * Handles dynamic loading by looking up names in a pokedex file and 
 * unpacking specific assets from a data archive before loading.
 */
void PokeSprite::SelectPokemonSprite(bool shiny, en_SpriteType type, int pokeID){

  // Open the pokedex index to find the name associated with the ID
  std::ifstream file("../assets/SpritesAnimated/pokedex.txt");
  if(!file.is_open()) return;

  std::string nombre;
  int i = 1;
  while(std::getline(file, nombre)){
    if(i++ == pokeID) break;
  }
  file.close();

  // Clean the string: remove spaces and hyphens to match file naming conventions
  nombre.erase(std::remove(nombre.begin(), nombre.end(), ' '), nombre.end());
  nombre.erase(std::remove(nombre.begin(), nombre.end(), '-'), nombre.end());

  std::string isShiny = shiny ? " shiny" : "";
  std::string whichType;

  // Determine the directory based on the sprite perspective
  switch(type){
    case type_Attacker: whichType = "Back"; break;
    case type_Defender: whichType = "Front"; break;
    case type_Icon:     whichType = "Icons"; break;
  }

  char filesprite[128];
  char filedatabase[128];
  char fileindex[128];

  // Construct file paths for the specific sprite and its source archives
  snprintf(filesprite, 128, "../assets/SpritesAnimated/%s%s/%s.png", whichType.c_str(), isShiny.c_str(), nombre.c_str());
  snprintf(filedatabase, 128, "../assets/SpritesAnimated/%s%s/_sprites.dat", whichType.c_str(), isShiny.c_str());
  snprintf(fileindex, 128, "../assets/SpritesAnimated/%s%s/_index.txt", whichType.c_str(), isShiny.c_str());

  // Unpack the specific PNG from the .dat file before loading it into memory
  UnpackSprite(nombre.c_str(), fileindex, filedatabase);
  TextureManager::Load(sRenderer_, textureID, filesprite);

  // Clean up the temporary unpacked file
  remove(filesprite);
}