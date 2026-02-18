#pragma once

#ifndef _GAME_H_ 
#define _GAME_H_

#include "trainer.h"

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
};

class Game {
public:
  en_SceneManager sceneManager = kSceneInit; // Current scene is being played
  en_FightManager fightManager = kFightInit; // Curent part in the fight is being played

  Trainer* trainer1;  // Trainer 1 in fight
  Trainer* trainer2;  // Trainer 2 in fight

  PlayerActions playerActions;

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
  PlayerActions DecideActions(PlayerActions* act);
  //Some actions may not perform, so we check them here, if not return to DecideActions();
  bool ValidateAction(PlayerActions act);
  //Se realiza accion
  void PlayActions();
  //Ocurren sucesos
  void ResultFromActions();
  //__

  //Finaliza combate
  // 0 -> Not ended | 1 -> Trainer 1 won | 2 -> Trainer 2 won
  int EndedBattle(Trainer* _trainer1, Trainer* _trainer2);
  //Ganador / Perdedor
  //





  
};

#endif //_GAME_H_