#include "TextureManager.h"

std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

bool TextureManager::Load(SDL_Renderer* renderer, const std::string& id, const std::string& path){ 

  SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
  SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);

  if (!tex) return false;
  textures[id] = tex;
  SDL_SetTextureScaleMode(textures[id], SDL_SCALEMODE_NEAREST);
  return true;
}

SDL_Texture* TextureManager::Get(const std::string& id){
  return textures[id];
}

void TextureManager::Clear(){
  for (auto& pair : textures)
  {
    SDL_DestroyTexture(pair.second);
  }
  textures.clear();
}