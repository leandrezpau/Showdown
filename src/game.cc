#define _GAME_CC_
#ifdef _GAME_CC_

#include "game.h"

void Game::InitBattle(Trainer* _trainer1, Trainer* _trainer2){
  std::cout << "\n" << _trainer1->name << " you are being challenged by " << _trainer2->name;

  trainer1 = _trainer1;
  trainer2 = _trainer2;

  HealPlayer(trainer1);
  HealPlayer(trainer2);

  ResetAction();
}

int Game::EndedBattle(Trainer* _trainer1, Trainer* _trainer2){
  if(!_trainer1->HasAvailablePokemon()) return 1;
  if(!_trainer2->HasAvailablePokemon()) return 2;
  return 0;
}

void Game::HealPlayer(Trainer* healedTrainer){
  for(int i = 0; i < healedTrainer->team.size(); i++){
    if(true){ // Sanity check if pokemon exists
      Pokemon* poke = &healedTrainer->team[i];

      //Movement PP
      for(int e = 0; e < poke->movement.size(); e++){
        poke->movement[e].currentPP = poke->movement[e].pp;
      }
      //Current Stats to Base Stats
      poke->currentStats = poke->baseStats;

      //Giving him alive again
      poke->state = PokeState::kStateAlive;
    }
  }
}

void Game::DecideActions() {
  if (running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return;
      }

      if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {

        int key = event.key.scancode;

        //CHOOSE TYPE OF ACTION
        if (act.playerAction[0] == kActionNULL) {

          if (key == SDL_SCANCODE_1) {
            act.playerAction[0] = kActionAttack;
            std::cout << "\nAttacking, Now choose movement to use";
            int kMoves = trainer1->GetCurrentPokemon().movement.size();
            for(int i = 0; i < 4; i++){
              if(i < kMoves){
                std::cout << "\n" << i + 1 << ": "<< trainer1->GetCurrentPokemon().movement[i].moveName;
              }else{
                std::cout << "\n" << i + 1 << ": NullMove";
              }
            }
          }

          else if (key == SDL_SCANCODE_2) {
            act.playerAction[0] = kActionChangePoke;
            std::cout << "\nChanging pokemon, Now choose which pokemon to use";
            int kPokes = trainer1->team.size();
            for(int i = 0; i < 6; i++){
              if(i < kPokes){
                std::cout << "\n" << i + 1 << ": "<< trainer1->team[i].name;
              }else{
                std::cout << "\n" << i + 1 << ": NoPoke";
              }
            }
          }
        } else {
          //CHOOSING INDEX
          if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_6) {

            int index = key - SDL_SCANCODE_1;

            //If changing pokemon
            if (act.playerAction[0] == kActionChangePoke) {
              act.playerIndex[0] = index;
              if(ValidateAction(act)){
                return;
              }else{
                act.playerIndex[0] = 0;
              }
            }

            //If attacking
            Pokemon poke = trainer1->team[trainer1->currentPokemonIndex];
            if (act.playerAction[0] == kActionAttack) {
              act.playerIndex[0] = index;
              if (ValidateAction(act)) {
                return;
              } else {
                act.playerIndex[0] = 0;
              }
            }
          }
          if(key = SDL_SCANCODE_ESCAPE){
            ResetAction();
          }
        }
      }
    }
  }
}
bool Game::ValidateAction(PlayerActions act_){
  bool isValid = true;
  switch(act_.playerAction[0]){
    //IF PLAYER WANTS TO ATTACK
    case kActionAttack:{
      Pokemon& poke = trainer1->GetCurrentPokemon();
      if(poke.movement.size() < act_.playerIndex[0] + 1){
        isValid = false;
        std::cout << "\nYour poke does't have a move in that slot";
        break;
      }else{
        if(poke.movement[act_.playerIndex[0]].currentPP <= 0){
          isValid = false;
          std::cout << "\nThat Movement doesn't have PP";
          break;
        }else if(poke.movement[act_.playerIndex[0]].index == mv_NULL){
          isValid = false;
          std::cout << "\nThat not a valid move";
          break;
        }
      }
    }
    //IF PLAYER WANTS TO CHOOSE POKEMON
    case kActionChangePoke:{
      if(trainer1->team.size() < act_.playerIndex[0] + 1){
        isValid = false;
        std::cout << "\nYou don't have pokemon in that slot";
        break;
      }else{
        if(trainer1->team[act_.playerIndex[0]].currentStats.HP <= 0){
          isValid = false;
          std::cout << "\nThat poke is fainted";
          break;
        }
      }
      break;
    }
    //IF ACTION WAS NULL (SOMETHING CRASHED)
    case kActionNULL:{
      std::cout << "\nNo action played";
      break;
    }
  }
  act.decided[0] = isValid;
  return isValid;
}
//Se realiza accion
void Game::PlayActions(){
  if(act.decided[0] == true){
    switch(act.playerAction[0]){
      case kActionChangePoke:{
        trainer1->ChangePokemon(act.playerIndex[0]);
        std::cout << "\nChanging Pokemon to " << trainer1->GetCurrentPokemon().name;
        ResetAction();
        break;
      }
      case kActionAttack:{
        std::cout << "\n" << trainer1->GetCurrentPokemon().name << " Attacked " << trainer2->GetCurrentPokemon().name;
        trainer1->GetCurrentPokemon().UseMove(trainer2->GetCurrentPokemon(), trainer1->GetActivePokemon()->movement[act.playerIndex[0]]);
        ResetAction();
        break;
      }
      case kActionNULL:{
        std::cout << "\nNo action in this frame";
        break;
      }
      default:{
        std::cout << "\nPOR AQUI NO HAY QUE ENTRAR ESTA MAL ESTA ROTO JODER CON LO QUE ME HABIA COSTADO HACER ESTAS PUTAS FUNCIONES";
      }
    }
  }
}
//Ocurren sucesos
void Game::ResultFromActions(){
  if(!trainer1->HasAvailablePokemon()) std::cout << "Trainer 1 has all his pokemon fainted";
  if(!trainer2->HasAvailablePokemon()) std::cout << "Trainer 2 has all his pokemon fainted";
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
      DecideActions();
      //Se realiza accion
      PlayActions();
      //Ocurren sucesos
      ResultFromActions();
      //__

      //Finaliza combate
      // 0 -> Not ended | 1 -> Trainer 1 won | 2 -> Trainer 2 won
      winner = EndedBattle(trainer1, trainer2);
      switch(winner){
        case 0:{
          break;
        } 

        case 1:
        case 2:{
          sceneManager = kSceneAfterFight; 
          break;
        } 
      }
      
    }
  }
}

void Game::ResetAction(){
  for(int i = 0; i < 2; i++){
    act.playerAction[i] = kActionNULL;
    act.playerIndex[i] = 0;
    act.decided[i] = false;
  }

  std::cout << "\nPress 1 to attack\nPress 2 to change pokemon";
}

void Game::ProcessInput(){

}

#endif //_GAME_CC_