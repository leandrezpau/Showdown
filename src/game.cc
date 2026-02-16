#define _GAME_CC_
#ifdef _GAME_CC_

#include "game.h"

void Game::InitBattle(Trainer* _trainer1, Trainer* _trainer2){
  std::cout << "\n" << _trainer1->name << "you are being challenged by " << _trainer2->name;

  trainer1 = _trainer1;
  trainer2 = _trainer2;

  HealPlayer(trainer1);
  HealPlayer(trainer2);
}

void Game::PlayBattle(){
  switch(EndedBattle(trainer1, trainer2)){
    case 1:
    case 2:{
      sceneManager = kSceneAfterFight;
    }
    case 0:{
      
    }
  }
}
void Game::PokeFainted(){

}

int Game::EndedBattle(Trainer* _trainer1, Trainer* _trainer2){
  if(_trainer1->HasAvailablePokemon()) return 1;
  if(_trainer2->HasAvailablePokemon()) return 2;
  return 0;
}

void Game::HealPlayer(Trainer* healedTrainer){
  for(int i = 0; i < healedTrainer->team.size(); i++){
    if(true){ // Sanity check if pokemon exists
      Pokemon* poke = &healedTrainer->team[i];

      //Movement PP
      for(int e = 0; e < 4; e++){
        poke->movement[e].currentPP = poke->movement[e].pp;
      }
      //Current Stats to Base Stats
      poke->currentStats = poke->baseStats;

      //Giving him alive again
      poke->state = PokeState::kStateAlive;
    }
  }
}
#endif //_GAME_CC_