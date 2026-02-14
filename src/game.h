#pragma once
#ifndef _GAME_H_ 
#define _GAME_H_

enum en_SceneManager {
  kSceneInit = 0,     // Init of game
  kSceneGameMode,     // Select Gamemode
  kSceneChoseTeam,    // Choose team
  kSceneFight,        // Fighting Scene
  kSceneAfterFight,   // Scene after fight
  kSceneEnd,          // Final scene
};


class Game {

};

#endif //_GAME_H_