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

PlayerActions Game::DecideActions(PlayerActions* act) {
  bool choosing = true;

  std::cout << "\nPress 1 to attack\nPress 2 to change pokemon";

  while (choosing && running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return *act;
      }

      if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {

        int key = event.key.scancode;

        //Choose type of action
        if (act->playerAction[0] == kActionNULL) {

          if (key == SDL_SCANCODE_1) {
            act->playerAction[0] = kActionAttack;
            std::cout << "\nAttacking, Now choose movement to use";
          }

          else if (key == SDL_SCANCODE_2) {
            act->playerAction[0] = kActionChangePoke;
            std::cout << "\nChanging pokemon, Now choose which pokemon to use";
          }
        }

        //Choose index in action
        else {

          if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_6) {

            int index = key - SDL_SCANCODE_1;

            //If changing pokemon
            if (act->playerAction[0] == kActionChangePoke && index <= trainer1->team.size() - 1) {
              act->playerIndex[0] = index;
              if(ValidateAction(*act)){
                return *act;
              }else{
                act->playerIndex[0] = 0;
                act->playerIndex[1] = 0;
              }
            }

            //If attacking
            Pokemon poke = trainer1->team[trainer1->currentPokemonIndex];
            if (act->playerAction[0] == kActionAttack && index <= poke.movement.size() - 1) {
              act->playerIndex[0] = index;
              if(ValidateAction(*act)){
                return *act;
              }else{
                act->playerIndex[0] = 0;
                act->playerIndex[1] = 0;
              }
            }
          }
        }
      }
    }
  }

  return *act;
}
bool Game::ValidateAction(PlayerActions act){
  bool isValid = true;
  switch(act.playerAction[0]){
    case kActionAttack:{
      Pokemon poke = trainer1->GetCurrentPokemon();
      if(poke.movement[act.playerIndex[0]].currentPP <= 0){
        isValid = false;
        std::cout << "\nThat Movement doesn't have PP";
        break;
      } 
      if(poke.movement[act.playerIndex[0]].index == mv_NULL){
        isValid = false;
        std::cout << "\nThat not a valid move";
        break;
      }
    }
    case kActionChangePoke:{
      if(trainer1->team.size() < act.playerIndex[0]){
        isValid = false;
        std::cout << "\nYou don't have pokemon in that slot";
      }else{
        if(trainer1->team[act.playerIndex[0]].currentStats.HP <= 0){
          isValid = false;
          std::cout << "\nThat poke is fainted";
        }
      }
    }
    case kActionNULL:{
      std::cout << "\nNo action played";
    }
  }
  return isValid;
}
//Se realiza accion
void Game::PlayActions(){

}
//Ocurren sucesos
void Game::ResultFromActions(){

}

void Game::PlayBattle(){
  switch(EndedBattle(trainer1, trainer2)){
    case 1:
    case 2:{
      sceneManager = kSceneAfterFight;
    }
    case 0:{
      //Lanzan primer pokemon

      //__
      //Ambos eligen que hacer
      playerActions = DecideActions(&playerActions);
      //Se realiza accion
      PlayActions();
      //Ocurren sucesos
      ResultFromActions();
      //__

      //Finaliza combate
      // 0 -> Not ended | 1 -> Trainer 1 won | 2 -> Trainer 2 won
      winner = EndedBattle(trainer1, trainer2);
      switch(winner){
        case 0: break;

        case 1:
        case 2: sceneManager = kSceneAfterFight; break;
      }
      
    }
  }
}

#endif //_GAME_CC_