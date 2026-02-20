#define _GAME_CC_
#ifdef _GAME_CC_
#include "game.h"
#include "battleai.h"
#include <iostream>
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

  // Limpiamos las acciones por si acaso (evita basura de turnos anteriores)
  act->playerAction[0] = kActionNULL;
  act->playerAction[1] = kActionNULL;

  std::cout << "\nPress 1 to attack\nPress 2 to change pokemon";

  // === TURNO JUGADOR 1 (HUMANO) ===
  while (choosing && running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return *act;
      }

      if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        int key = event.key.scancode;

        // Choose type of action
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
        // Choose index in action
        else {
          if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_6) {
            int index = key - SDL_SCANCODE_1;

            // If changing pokemon
            if (act->playerAction[0] == kActionChangePoke && index <= trainer1->team.size() - 1) {
              act->playerIndex[0] = index;
              if (ValidateAction(*act)) {
                choosing = false; // <-- CAMBIO AQUÍ: Rompemos el bucle en lugar de retornar
                break;
              }
              else {
                act->playerIndex[0] = 0;
                act->playerAction[0] = kActionNULL; // Reseteamos si es inválido
              }
            }

            // If attacking
            Pokemon poke = trainer1->team[trainer1->currentPokemonIndex];
            if (act->playerAction[0] == kActionAttack && index <= poke.movement.size() - 1) {
              act->playerIndex[0] = index;
              if (ValidateAction(*act)) {
                choosing = false; // <-- CAMBIO AQUÍ: Rompemos el bucle en lugar de retornar
                break;
              }
              else {
                act->playerIndex[0] = 0;
                act->playerAction[0] = kActionNULL; // Reseteamos si es inválido
              }
            }
          }
        }
      }
    }
  }

  // === TURNO JUGADOR 2 (IA) ===
  if (running && trainer2->isAI) {
    std::cout << "\n" << trainer2->name << " (IA) esta decidiendo su jugada...\n";

    // Llamamos a la IA pasándole el entrenador rival y el Pokémon activo del jugador
    // Usamos GetActivePokemon() que devuelve un puntero, tal como lo definiste en trainer.h
    PlayerActions aiDecision = BattleAI::GetBestAction(trainer2, trainer1->GetActivePokemon());

    // Guardamos la decisión de la IA en el índice 1 (correspondiente al Jugador 2)
    act->playerAction[1] = aiDecision.playerAction[0];
    act->playerIndex[1] = aiDecision.playerIndex[0];
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
void Game::PlayActions() {
  std::cout << "\n--- COMIENZA EL TURNO ---";

  // Punteros rápidos a los Pokémon activos actuales
  Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
  Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

  // === 1. FASE DE CAMBIOS (PRIORIDAD ALTA) ===
  // Si el Jugador 1 cambia de Pokémon
  if (playerActions.playerAction[0] == kActionChangePoke) {
    trainer1->currentPokemonIndex = playerActions.playerIndex[0];
    p1 = &trainer1->team[trainer1->currentPokemonIndex];
    std::cout << "\n" << trainer1->name << " retiro a su Pokemon y envio a " << p1->name << "!";
  }

  // Si el Jugador 2 (IA o Humano) cambia de Pokémon
  if (playerActions.playerAction[1] == kActionChangePoke) {
    trainer2->currentPokemonIndex = playerActions.playerIndex[1];
    p2 = &trainer2->team[trainer2->currentPokemonIndex];
    std::cout << "\n" << trainer2->name << " retiro a su Pokemon y envio a " << p2->name << "!";
  }

  // === 2. FASE DE ATAQUES (RESOLUCIÓN POR VELOCIDAD) ===
  bool p1Attacks = (playerActions.playerAction[0] == kActionAttack);
  bool p2Attacks = (playerActions.playerAction[1] == kActionAttack);

  // Determinar quién ataca primero si ambos decidieron atacar
  bool p1GoesFirst = true;
  if (p1Attacks && p2Attacks) {
    if (p2->currentStats.Vel > p1->currentStats.Vel) {
      p1GoesFirst = false;
    }
    else if (p2->currentStats.Vel == p1->currentStats.Vel) {
      // Speed Tie: Empate de velocidad, se decide con una moneda al aire
      p1GoesFirst = (rand() % 2 == 0);
    }
  }

  // Función lambda auxiliar para no repetir el código de atacar dos veces
  auto executeAttack = [](Pokemon* attacker, Pokemon* defender, int moveIndex) {
    // Solo atacamos si AMBOS siguen vivos (para evitar golpear al aire si uno ya murió)
    if (attacker->currentStats.HP > 0 && defender->currentStats.HP > 0) {
      Movement& move = attacker->movement[moveIndex];

      // Restar 1 PP al movimiento usado
      if (move.currentPP > 0) move.currentPP--;

      // Llamamos a tu función de daño!
      attacker->UseMove(*defender, move);
    }
    };

  // Ejecutamos los ataques en el orden calculado
  if (p1GoesFirst) {
    if (p1Attacks) executeAttack(p1, p2, playerActions.playerIndex[0]);
    if (p2Attacks) executeAttack(p2, p1, playerActions.playerIndex[1]);
  }
  else {
    if (p2Attacks) executeAttack(p2, p1, playerActions.playerIndex[1]);
    if (p1Attacks) executeAttack(p1, p2, playerActions.playerIndex[0]);
  }
}
//Ocurren sucesos
void Game::ResultFromActions() {
  std::cout << "\n--- RESOLUCION DEL TURNO ---";

  // Obtenemos los Pokémon que acaban de combatir
  Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
  Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

  // === 1. COMPROBAR SI EL POKÉMON DEL JUGADOR 1 CAYÓ ===
  if (p1->currentStats.HP <= 0 && p1->state != kStateFainted) {
    p1->currentStats.HP = 0; // Aseguramos que no queden números negativos
    p1->state = kStateFainted;
    std::cout << "\n!" << p1->name << " de " << trainer1->name << " se ha debilitado!";

    // Si al jugador 1 le quedan Pokémon, le pedimos que saque otro
    if (trainer1->HasAvailablePokemon()) {
      bool choosing = true;
      std::cout << "\nElige a tu proximo Pokemon (1 - " << trainer1->team.size() << "): ";

      // Bucle rápido para forzar el cambio antes del siguiente turno
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
              // Verificamos que el índice exista y el Pokémon esté vivo
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

  if (p2->currentStats.HP <= 0 && p2->state != kStateFainted) {
    p2->currentStats.HP = 0;
    p2->state = kStateFainted;
    std::cout << "\n!" << p2->name << " de " << trainer2->name << " se ha debilitado!";

    if (trainer2->HasAvailablePokemon()) {
      if (trainer2->isAI) {
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