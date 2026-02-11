/* debug-text.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some text
 * using SDL_RenderDebugText() every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */


#include "pokemon.h"
#include "sprites.h"
#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

#include <string>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

en_SceneManager sceneManager = en_SceneManager::kSceneInit;

#pragma region Main
/*
    .___  ___.      ___       __  .__   __. 
    |   \/   |     /   \     |  | |  \ |  | 
    |  \  /  |    /  ^  \    |  | |   \|  | 
    |  |\/|  |   /  /_\  \   |  | |  . `  | 
    |  |  |  |  /  _____  \  |  | |  |\   | 
    |__|  |__| /__/     \__\ |__| |__| \__|     

*/
int main(int argc, char* argv[]){

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Pokemon Showdown", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  SDL_SetRenderVSync(renderer, 1);

  
  bool running = true;

  Sprite poke1{renderer};
  Sprite poke2{renderer};

 
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) running = false;
    }

    switch(sceneManager){
      case en_SceneManager::kSceneInit:{  //CURRENT SCENE

        poke1.SelectSprite(true, Sprite::en_SpriteType::type_Attacker, 400);
        poke1.InitSpriteSrc();
        poke1.InitSpriteDst(Sprite::en_SpriteType::type_Attacker, 100, 300);
        

        poke2.SelectSprite(true, Sprite::en_SpriteType::type_Defender, 555);
        poke2.InitSpriteSrc();
        poke2.InitSpriteDst(Sprite::en_SpriteType::type_Defender, 300, 30);
        

        sceneManager = en_SceneManager::kSceneGameMode;
        break;
      }
      case en_SceneManager::kSceneGameMode:{  //CURRENT SCENE
        const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

        //DRAW INIT
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        /* as you can see from this, rendering draws over whatever was drawn before it. */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
        SDL_RenderClear(renderer);  /* start with a blank canvas. */

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
        SDL_RenderDebugText(renderer, 272, 100, "Hello world!");
        SDL_RenderDebugText(renderer, 224, 150, "This is some debug text.");

        SDL_SetRenderDrawColor(renderer, 51, 102, 255, SDL_ALPHA_OPAQUE);  /* light blue, full alpha */
        SDL_RenderDebugText(renderer, 184, 200, "You can do it in different colors.");
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */

        SDL_SetRenderScale(renderer, 4.0f, 4.0f);
        SDL_RenderDebugText(renderer, 14, 65, "It can be scaled.");
        SDL_SetRenderScale(renderer, 1.0f, 1.0f);
        SDL_RenderDebugText(renderer, 64, 350, "This only does ASCII chars. So this laughing emoji won't draw: 🤣");

        SDL_RenderDebugTextFormat(renderer, (float) ((WINDOW_WIDTH - (charsize * 46)) / 2), 400, "(This program has been running for %" SDL_PRIu64 " seconds.)", SDL_GetTicks() / 1000);

        //poke1.ApplyFilter(255, 100, 100);
        poke1.DrawSprite();
        poke2.DrawSprite();

        //DRAW CLEAR
        SDL_RenderPresent(renderer);

        //sceneManager = en_SceneManager::kSceneChoseTeam;
        break;
      }
      case en_SceneManager::kSceneChoseTeam:{ //CURRENT SCENE

        sceneManager = en_SceneManager::kSceneFight;
        break;
      }
      case en_SceneManager::kSceneFight:{     //CURRENT SCENE

        sceneManager = en_SceneManager::kSceneAfterFight;
        break;
      }
      case en_SceneManager::kSceneAfterFight:{ //CURRENT SCENE

        sceneManager = en_SceneManager::kSceneEnd;
        break;
      }
      case en_SceneManager::kSceneEnd:{       //CURRENT SCENE

        running = false;
        break;
      }
    }
  }

  return 0;
}
