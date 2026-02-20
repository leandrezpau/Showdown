#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
  static bool Load(SDL_Renderer* renderer, const std::string& id, const std::string& path);
  static SDL_Texture* Get(const std::string& id);
  static void Clear();

private:
  static std::unordered_map<std::string, SDL_Texture*> textures;
};