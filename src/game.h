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

class Game {
public:
  en_SceneManager sceneManager = kSceneInit; // Current scene is being played
  en_FightManager fightManager = kFightInit; // Curent part in the fight is being played
  Trainer* trainer1;  // Trainer 1 in fight
  Trainer* trainer2;  // Trainer 2 in fight

  void InitBattle(Trainer* _trainer1, Trainer* _trainer2);
  void PlayBattle();
  void PokeFainted();

  // 0 -> Not ended | 1 -> Trainer 1 lost | 2 -> Trainer 2 lost
  int EndedBattle(Trainer* _trainer1, Trainer* _trainer2);


  void HealPlayer(Trainer* healedTrainer);
};

#endif //_GAME_H_