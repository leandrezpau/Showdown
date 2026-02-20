/* debug-text.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some text
 * using SDL_RenderDebugText() every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */


#include "pokemon.h"
#include "sprites/sprites.h"
#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

#include <string>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 380

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
  system("cls");
  printf("\n\n");
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Pokemon Showdown", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  SDL_SetRenderVSync(renderer, 1);

  Game game;

  int currentPokemon = 1;
  int contador = 0;
  

  BaseSprite::SetSpritesRenderer(renderer);

  //ID, Level, Weight, Gender, Shiny, Renderer, TypeSprite
  Trainer train1{"Goldi", false};
  Trainer train2{"IA Trainer", true};

  train1.AddPokemon(Pokemon{6, 50, 0, true, en_SpriteType::type_Attacker});
  train1.AddPokemon(Pokemon{646, 50, 0, true, en_SpriteType::type_Attacker});
  train1.AddPokemon(Pokemon{6, 50, 0, true, en_SpriteType::type_Attacker});

  train2.AddPokemon(Pokemon{6, 50, 0, true, en_SpriteType::type_Defender});

  Sprite background;
 
  while (game.running) {
    switch(game.sceneManager){
      case en_SceneManager::kSceneInit:{  //CURRENT SCENE
        background.SetTextureID(1000);
        background.SelectSpriteFromRoute("../assets/background_Sprites/lava_battle.png");
        background.InitSpriteSrc(false);
        background.InitSpriteDst(0, 0, 1);

        game.InitBattle(&train1, &train2);

        game.sceneManager = en_SceneManager::kSceneGameMode;
        break;
      }
      case en_SceneManager::kSceneGameMode:{  //CURRENT SCENE
        //DRAW INIT
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        game.PlayBattle();
        //if(contador % 60 == 0) poke1.SetNewPokemon(++currentPokemon, 50, 0, true, poke1.typeSprite);

        background.DrawSprite();
        train1.team[train1.currentPokemonIndex].DrawSprite();
        train2.team[train2.currentPokemonIndex].DrawSprite();

        //DRAW CLEAR
        SDL_RenderPresent(renderer);
        contador++;
        //sceneManager = en_SceneManager::kSceneChoseTeam;
        break;
      }
      case en_SceneManager::kSceneChoseTeam:{ //CURRENT SCENE
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
        //DRAW CLEAR
        SDL_RenderPresent(renderer);
        
        game.sceneManager = en_SceneManager::kSceneFight;
        break;
      }
      case en_SceneManager::kSceneFight:{     //CURRENT SCENE

        game.sceneManager = en_SceneManager::kSceneAfterFight;
        break;
      }
      case en_SceneManager::kSceneAfterFight:{ //CURRENT SCENE

        game.sceneManager = en_SceneManager::kSceneEnd;
        break;
      }
      case en_SceneManager::kSceneEnd:{       //CURRENT SCENE

        game.running = false;
        break;
      }
    }
  }

  return 0;
}
