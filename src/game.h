#pragma once

#ifndef _GAME_H_ 
#define _GAME_H_

#include "trainer.h"
#include <SDL3_ttf/SDL_ttf.h>

enum en_SceneManager {
  kSceneInit = 0,     // Init of game
  kSceneGameMode,     // Select Gamemode
  kSceneChoseTeam,    // Choose team
  kSceneFight,        // Fighting Scene
  kSceneAfterFight,   // Scene after fight
  kSceneEnd,          // Final scene
};

enum en_FightManager {
  kFightInit = 0,       // Init of the fight
  kFightWaitingChoice,  // Waiting for players choice
  kFightPlayingChoice,  // Playing player's choice
  kFightResults,        // Showing choices results
  kFightEnd,            // Fight ended
};

enum en_Actions {
  kActionNULL = 0,
  kActionAttack,
  kActionChangePoke,
  
};

struct PlayerActions {
  // NULL No action, Attack, or ChangePoke
  en_Actions playerAction[2];

  // If player attacks, 0 - 3 (which attack) If player changes 0 - 5 (which poke)
  // If player chooses attacks & plays 5 it is filtered later (no problem about that)
  int playerIndex[2];

  bool decided[2];
};

class Game {
public:
  en_SceneManager sceneManager = kSceneInit; // Current scene is being played
  en_FightManager fightManager = kFightInit; // Curent part in the fight is being played

  SDL_Renderer* renderer;
  TTF_Font* font;

  Trainer* trainer1;  // Trainer 1 in fight
  Trainer* trainer2;  // Trainer 2 in fight

  PlayerActions playerActions;

  Sprite background;
  Sprite pokebar;

  int winner = 0;
  bool running = true;


  void HealPlayer(Trainer* healedTrainer);

  void PlayBattle();
  //>>Sistema de Batalla<<

  //Se eligen entrenadores
  void InitBattle(Trainer* _trainer1, Trainer* _trainer2);
  //Lanzan primer pokemon
  //__
  //Ambos eligen que hacer
  void DecideActions();
  //Some actions may not perform, so we check them here, if not return to DecideActions();
  bool ValidateAction(PlayerActions act_);
  //Se realiza accion
  void PlayActions();
  //Ocurren sucesos
  void ResultFromActions();
  //__ 
  void DrawGame();
  //Finaliza combate
  // 0 -> Not ended | 1 -> Trainer 1 won | 2 -> Trainer 2 won
  int EndedBattle(Trainer* _trainer1, Trainer* _trainer2);
  //Ganador / Perdedor
  //
  void ResetAction();
  void DrawCombatHUD();

  void DrawText(const std::string& str, float posX, float posY, bool loweredText, float scale = 2.0f, SDL_Color color = {168, 184, 184, 255});
  void DrawLifeBar(Stats stats, float posX, float posY, float lenght, float height, bool big);
  void DrawMovement(Movement move, float posX, float posY, bool drawType);

  void DrawSelectPokemon();
  int SelectBattleAction(SDL_Event event_);

  Game(SDL_Renderer* renderer_, TTF_Font* font_);
};

#endif //_GAME_H_