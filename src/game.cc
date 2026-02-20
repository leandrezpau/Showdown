#define _GAME_CC_
#ifdef _GAME_CC_
#include "game.h"
#include "battleai.h"
#include <iostream>

// Configura los entrenadores al inicio del combate y cura a sus equipos
void Game::InitBattle(Trainer* _trainer1, Trainer* _trainer2) {
  std::cout << "\n" << _trainer1->name << "you are being challenged by " << _trainer2->name;

  trainer1 = _trainer1;
  trainer2 = _trainer2;

  HealPlayer(trainer1);
  HealPlayer(trainer2);

  ResetAction();
}

// Comprueba si la batalla ha terminado verificando si a algun entrenador no le quedan Pokemon vivos
// Devuelve: 0 -> Combate activo | 1 -> Gana Entrenador 1 | 2 -> Gana Entrenador 2
int Game::EndedBattle(Trainer* _trainer1, Trainer* _trainer2) {
  if (_trainer1->HasAvailablePokemon()) return 1;
  if (_trainer2->HasAvailablePokemon()) return 2;
  return 0;
}

// Restaura HP, PP y estados alterados de todo el equipo de un entrenador
void Game::HealPlayer(Trainer* healedTrainer) {
  for (int i = 0; i < healedTrainer->team.size(); i++) {
    if (true) { // Sanity check if pokemon exists
      Pokemon* poke = &healedTrainer->team[i];

      //Movement PP
      for(int e = 0; e < poke->movement.size(); e++){
        poke->movement[e].currentPP = poke->movement[e].pp;
      }
      poke->currentStats = poke->baseStats;
      poke->state = PokeState::kStateAlive;
    }
  }
}
// Fase de Seleccion: Pide la accion al Jugador 1 y consulta a la IA para el Jugador 2
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

// Motor de Ejecucion: Procesa las acciones elegidas respetando el sistema de prioridades de Pokemon
void Game::PlayActions() {
  std::cout << "\n--- COMIENZA EL TURNO ---";

  Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
  Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

  // === PRIORIDAD 1: CAMBIOS DE POKEMON ===
  // Los cambios siempre ocurren antes que cualquier ataque
  if (playerActions.playerAction[0] == kActionChangePoke) {
    trainer1->currentPokemonIndex = playerActions.playerIndex[0];
    p1 = &trainer1->team[trainer1->currentPokemonIndex];
    std::cout << "\n" << trainer1->name << " retiro a su Pokemon y envio a " << p1->name << "!";
  }

  if (playerActions.playerAction[1] == kActionChangePoke) {
    trainer2->currentPokemonIndex = playerActions.playerIndex[1];
    p2 = &trainer2->team[trainer2->currentPokemonIndex];
    std::cout << "\n" << trainer2->name << " retiro a su Pokemon y envio a " << p2->name << "!";
  }

  // === PRIORIDAD 2: ATAQUES (Resolucion por Velocidad) ===
  bool p1Attacks = (playerActions.playerAction[0] == kActionAttack);
  bool p2Attacks = (playerActions.playerAction[1] == kActionAttack);

  bool p1GoesFirst = true;
  if (p1Attacks && p2Attacks) {
    if (p2->currentStats.Vel > p1->currentStats.Vel) {
      p1GoesFirst = false;
    }
    else if (p2->currentStats.Vel == p1->currentStats.Vel) {
      // Speed Tie (Empate de velocidad): Se decide a cara o cruz
      p1GoesFirst = (rand() % 2 == 0);
    }
  }

  // Lambda auxiliar para ejecutar ataques comprobando antes si ambos siguen vivos
  auto executeAttack = [](Pokemon* attacker, Pokemon* defender, int moveIndex) {
    // Si el atacante o el defensor murieron antes en este mismo turno, el ataque no ocurre
    if (attacker->currentStats.HP > 0 && defender->currentStats.HP > 0) {
      Movement& move = attacker->movement[moveIndex];
      if (move.currentPP > 0) move.currentPP--;
      attacker->UseMove(*defender, move);
    }
    };

  // Ejecutamos en el orden calculado
  if (p1GoesFirst) {
    if (p1Attacks) executeAttack(p1, p2, playerActions.playerIndex[0]);
    if (p2Attacks) executeAttack(p2, p1, playerActions.playerIndex[1]);
  }
  else {
    if (p2Attacks) executeAttack(p2, p1, playerActions.playerIndex[1]);
    if (p1Attacks) executeAttack(p1, p2, playerActions.playerIndex[0]);
  }
}

// Fase Final del Turno: Revisa caidos y fuerza la entrada de nuevos Pokemon al campo
void Game::ResultFromActions() {
  std::cout << "\n--- RESOLUCION DEL TURNO ---";

  Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
  Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

  // Comprueba si el Pokemon del JUGADOR 1 se ha desmayado
  if (p1->currentStats.HP <= 0 && p1->state != kStateFainted) {
    p1->currentStats.HP = 0;
    p1->state = kStateFainted;
    std::cout << "\n!" << p1->name << " de " << trainer1->name << " se ha debilitado!";

    // Si le quedan Pokemon vivos, forzamos un cambio via consola/SDL
    if (trainer1->HasAvailablePokemon()) {
      bool choosing = true;
      std::cout << "\nElige a tu proximo Pokemon (1 - " << trainer1->team.size() << "): ";

      while (choosing && running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_EVENT_QUIT) {
            running = false;
            return;
          }
          if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            int key = event.key.scancode;
            if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_6) {
              int index = key - SDL_SCANCODE_1;
              if (index < trainer1->team.size() && trainer1->team[index].currentStats.HP > 0) {
                trainer1->currentPokemonIndex = index;
                std::cout << "\n" << trainer1->name << " envia a " << trainer1->team[index].name << "!";
                choosing = false;
              }
              else {
                std::cout << "\nEse Pokemon no es valido o esta debilitado. Elige otro.";
              }
            }
          }
        }
      }
    }
  }

  // Comprueba si el Pokemon del JUGADOR 2 (IA) se ha desmayado
  if (p2->currentStats.HP <= 0 && p2->state != kStateFainted) {
    p2->currentStats.HP = 0;
    p2->state = kStateFainted;
    std::cout << "\n!" << p2->name << " de " << trainer2->name << " se ha debilitado!";

    if (trainer2->HasAvailablePokemon()) {
      if (trainer2->isAI) {
        // La IA elige automaticamente a su mejor opcion de reserva
        Pokemon* currentP1 = &trainer1->team[trainer1->currentPokemonIndex];
        std::pair<int, float> aiSwitch = BattleAI::ChooseSwitch(trainer2, currentP1);

        if (aiSwitch.first != -1) {
          trainer2->currentPokemonIndex = aiSwitch.first;
          std::cout << "\n" << trainer2->name << " envia a " << trainer2->team[trainer2->currentPokemonIndex].name << "!";
        }
      }
    }
  }
}

// Bucle principal de la Escena de Combate
void Game::PlayBattle() {
  switch (EndedBattle(trainer1, trainer2)) {
  case 1:
  case 2:
    sceneManager = kSceneAfterFight;
    break; // A�adido un break preventivo

  case 0:
    // 1. Ambos eligen que hacer
    DecideActions();
    // 2. Se realizan las acciones por orden de prioridad/velocidad
    PlayActions();
    // 3. Se resuelven los desmayos y se limpia el turno
    ResultFromActions();

    // Comprobamos si la partida termino en este turno
    winner = EndedBattle(trainer1, trainer2);
    switch (winner) {
    case 0: break;
    case 1:
    case 2: sceneManager = kSceneAfterFight; break;
    }
    break; // A�adido un break preventivo
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