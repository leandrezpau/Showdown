#define _GAME_CC_
#ifdef _GAME_CC_
#include "game.h"
#include "battleai.h"
#include <iostream>


Game::Game(SDL_Renderer* renderer_, TTF_Font* font_){
  background.SetTextureID(background.GetTextureID());
  background.SelectSpriteFromRoute("../assets/HUD/lava_battle_hud.png");
  background.InitSpriteSrc(false);
  background.InitSpriteDst(0, 0, 1);

  pokebar.SetTextureID(pokebar.GetTextureID());
  pokebar.SelectSpriteFromRoute("../assets/HUD/pokeBar.png");
  pokebar.InitSpriteSrc(false);
  pokebar.InitSpriteDst(0, 0, 1);

  renderer = renderer_;
  font = font_;
}
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
  if (!_trainer1->HasAvailablePokemon()) return 1;
  if (!_trainer2->HasAvailablePokemon()) return 2;
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
    // === TURNO JUGADOR 2 (IA) === 
    // Entra solo la primera vez q se llama la funcion
    if (running && trainer2->isAI && playerActions.decided[1] == false) {
      std::cout << "\n" << trainer2->name << " (IA) esta decidiendo su jugada...\n";

      // Llamamos a la IA pas�ndole el entrenador rival y el Pok�mon activo del jugador
      // Usamos GetActivePokemon() que devuelve un puntero, tal como lo definiste en trainer.h
      PlayerActions aiDecision = BattleAI::GetBestAction(trainer2, trainer1->GetActivePokemon());

      // Guardamos la decisi�n de la IA en el �ndice 1 (correspondiente al Jugador 2)
      playerActions.playerAction[1] = aiDecision.playerAction[0];
      playerActions.playerIndex[1] = aiDecision.playerIndex[0];
      playerActions.decided[1] = true;
    }

    // Poll event to get player input (which action he wants to)
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
        return;
      }
      
      if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        int key = event.key.scancode;
        if (trainer1->GetCurrentPokemon().currentStats.HP <= 0){
          if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            int key = event.key.scancode;
            if (key >= SDL_SCANCODE_1 && key <= SDL_SCANCODE_6) {
              int index = key - SDL_SCANCODE_1;
              if (index < trainer1->team.size() && trainer1->team[index].currentStats.HP > 0) {
                trainer1->currentPokemonIndex = index;
                std::cout << "\n" << trainer1->name << " envia a " << trainer1->team[index].name << "!";
              }
              else {
                std::cout << "\nEse Pokemon no es valido o esta debilitado. Elige otro.";
              }
            }
          }
        }else{
          // CHOOSE TYPE OF ACTION (Attack or Change)
          if (playerActions.playerAction[0] == kActionNULL) {
            // Key 1 Attack
            if (key == SDL_SCANCODE_1) {
              playerActions.playerAction[0] = kActionAttack;
              // Printing pokemon movements
              std::cout << "\nAttacking, Now choose movement to use";
              int kMoves = trainer1->GetCurrentPokemon().movement.size();
              for(int i = 0; i < 4; i++){
                if(i < kMoves){
                  std::cout << "\n" << i + 1 << ": "<< trainer1->GetCurrentPokemon().movement[i].moveName << " -> " << trainer1->GetCurrentPokemon().movement[i].moveType.typeName;
                }else{
                  std::cout << "\n" << i + 1 << ": NoMove";
                }
              }
            }
            // Key 2 Change
            else if (key == SDL_SCANCODE_2) {
              playerActions.playerAction[0] = kActionChangePoke;
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
              if (playerActions.playerAction[0] == kActionChangePoke) {
                playerActions.playerIndex[0] = index;
                if(ValidateAction(playerActions)){
                  return;
                }else{
                  playerActions.playerIndex[0] = 0;
                }
              }

              Pokemon poke = trainer1->team[trainer1->currentPokemonIndex];
              if (playerActions.playerAction[0] == kActionAttack) {
                playerActions.playerIndex[0] = index;
                if (ValidateAction(playerActions)) {
                  return;
                } else {
                  playerActions.playerIndex[0] = 0;
                }
              }
            }
            if(key == SDL_SCANCODE_ESCAPE){
              ResetAction();
            }
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
      Pokemon poke = trainer1->GetCurrentPokemon();
      if(poke.movement.size() < act_.playerIndex[0] + 1){
        isValid = false;
        std::cout << "\nYour poke does't have a move in that slot";
        break;
      }else{
        if(poke.movement[act_.playerIndex[0]].currentPP <= 0){
          isValid = false;
          std::cout << "\nThat Movement doesn't have PP";
          break;
        }
      }
      break;
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
  playerActions.decided[0] = isValid;
  return isValid;
}

// Motor de Ejecucion: Procesa las acciones elegidas respetando el sistema de prioridades de Pokemon
void Game::PlayActions() {
  if(playerActions.decided[0] == true){
    std::cout << "\n\n--- COMIENZA EL TURNO ---";

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
}

// Fase Final del Turno: Revisa caidos y fuerza la entrada de nuevos Pokemon al campo
void Game::ResultFromActions() {
  if(playerActions.decided[0] == true){
    std::cout << "\n\n--- RESOLUCION DEL TURNO ---";

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
    ResetAction();
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
void Game::DrawGame(){
  background.DrawSprite();
  if(trainer1->team[trainer1->currentPokemonIndex].currentStats.HP <= 0) trainer1->team[trainer1->currentPokemonIndex].ApplyFilter(255, 100, 100);
  trainer1->team[trainer1->currentPokemonIndex].DrawSprite();
  trainer2->team[trainer2->currentPokemonIndex].DrawSprite();

  int nMoves = trainer1->team[trainer1->currentPokemonIndex].movement.size();

  DrawCombatHUD();
}
void Game::DrawCombatHUD(){
  switch(playerActions.playerAction[0]){
    case kActionNULL:{
      if(trainer1->GetCurrentPokemon().currentStats.HP <= 0){
        for(int i = 0; i < trainer1->team.size(); i++){
          int jump = (i >= 3) ? 70 : 0;
          int row = i % 3;
          SDL_FRect iconDst = {
            74.0f + row * 190.0f, 
            395.0f + jump, 
            50.0f, 50.0f
          };
          SDL_FRect barDst = {
            70.0f + row * 190.0f, 
            385.0f + jump, 
            189.0f, 69.0f
          };
          pokebar.DrawSprite(150, barDst);
          trainer1->team[i].DrawIcon(iconDst);

          DrawText(trainer1->team[i].name, 70.0f + 190.0f * row + 54, 385.0f + 16 + jump, true);
          DrawLifeBar(
            trainer1->team[i].currentStats, 
            70.0f + row * 190.0f + 74, 
            385.0f + 48 + jump, 
            100, 
            8, 
            80);
          }
      }
      break;
    }
    case kActionChangePoke:{
      for(int i = 0; i < trainer1->team.size(); i++){
        int jump = (i >= 3) ? 74 : 0;
        int row = i % 3;
        SDL_FRect iconDst = {
          73.0f + row * 190.0f, 
          397.0f + jump, 
          50.0f, 50.0f
        };
        SDL_FRect barDst = {
          69.0f + row * 190.0f, 
          387.0f + jump, 
          189.0f, 69.0f
        };
        pokebar.DrawSprite(150, barDst);
        trainer1->team[i].DrawIcon(iconDst);

        DrawText(trainer1->team[i].name, 70.0f + 190.0f * row + 54, 385.0f + 16 + jump, true);
        DrawLifeBar(
          trainer1->team[i].currentStats, 
          69.0f + row * 190.0f + 74, 
          387.0f + 48 + jump, 
          100, 
          8, 
          80);
      }
      break;
    }
    case kActionAttack:{
      // Movements rectangles & text
      for(int i = 0; i < 2; i++){
        for(int e = 0; e < 2; e++){
          SDL_FRect rect = { 208.0f + 216.0f * i, 380.0f + 78.0f * e, 216.0f, 78.0f };
          SDL_SetRenderDrawColor(renderer, 250, i * 50, i * 27 + e * 99, 255);
          SDL_RenderFillRect(renderer, &rect);

          int index = i + e * 2;

          // Movements text
          DrawText(trainer1->GetCurrentPokemon().movement[index].moveName, 210.0f + 216.0f * i, 382.0f + 78.0f * e, true);
          // Movement PP Text
          char ppText[10];
          snprintf(ppText, 10, "%d/%d", trainer1->GetCurrentPokemon().movement[index].currentPP, trainer1->GetCurrentPokemon().movement[index].pp);
          DrawText(ppText, 210.0f + 216.0f * i, 420.0f + 78.0f * e, true);
        } 
      }
      break;
    }
  }
  // Normal HUD -> Player HP & Enemy HP
  DrawText(trainer1->GetCurrentPokemon().name, 419, 235, true);
  char hpText[10];
  snprintf(hpText, 10, "%.0f   %.0f", trainer1->GetCurrentPokemon().currentStats.HP, trainer1->GetCurrentPokemon().currentStats.maxHP);
  DrawText(hpText, 535, 272, true);
  DrawLifeBar(trainer1->GetCurrentPokemon().currentStats, 512, 262, 96, 4, 200);

  DrawText(trainer2->GetCurrentPokemon().name, 60, 32, true);
  DrawLifeBar(trainer2->GetCurrentPokemon().currentStats, 88, 60, 96, 4, 200);
}
void Game::ResetAction(){
  for(int i = 0; i < 2; i++){
    playerActions.playerAction[i] = kActionNULL;
    playerActions.playerIndex[i] = 0;
    playerActions.decided[i] = false;
  }

  std::cout << "\nPress 1 to attack\nPress 2 to change pokemon";
}
void Game::DrawText(const std::string& str, float posX, float posY, bool loweredText, SDL_Color color){
  std::string pokeName = str;
  if(loweredText && pokeName.size() >= 1){
    for(int i = 1; i < pokeName.size(); i++){
      pokeName[i] = std::tolower(pokeName[i]);
    }
  }
  SDL_Color shadowColor = {88, 88, 80, 255};
  SDL_Surface* surface1 = TTF_RenderText_Blended(font, pokeName.c_str(), pokeName.size(), color);
  SDL_Surface* surface2 = TTF_RenderText_Blended(font, pokeName.c_str(), pokeName.size(), shadowColor);

  if (!surface1 || !surface2) return;

  SDL_Texture* textToDraw1 = SDL_CreateTextureFromSurface(renderer, surface1);
  SDL_Texture* textToDraw2 = SDL_CreateTextureFromSurface(renderer, surface2);
  
  SDL_FRect dstText1 = { 
    posX + 2, 
    posY,
    (float) surface1->w,
    (float) surface1->h
  };
  SDL_FRect dstText2 = { 
    posX, 
    posY,
    (float) surface1->w,
    (float) surface1->h
  };

  // Shadow behind real text
  SDL_RenderTexture(renderer, textToDraw1, NULL, &dstText1);
  dstText1.x -= 2;
  dstText1.y += 2;
  SDL_RenderTexture(renderer, textToDraw1, NULL, &dstText1);
  dstText1.x += 2;
  SDL_RenderTexture(renderer, textToDraw1, NULL, &dstText1);

  // Real Text
  SDL_RenderTexture(renderer, textToDraw2, NULL, &dstText2);

  // Destroying every allocation
  SDL_DestroySurface(surface1);
  SDL_DestroySurface(surface2);
  SDL_DestroyTexture(textToDraw1);
  SDL_DestroyTexture(textToDraw2);
}

void Game::DrawLifeBar(Stats stats, float posX, float posY, float lenght, float width, unsigned char alpha){
  float barLenght = lenght * (stats.HP / stats.maxHP);
  SDL_FRect rect = { posX, posY, barLenght, width};

  SDL_Color barColor;
  float hpPercent = stats.HP / stats.maxHP;

  // Color by percentage
  if (hpPercent > 0.5f) {
    barColor = {0, 255, 0, alpha};    // Green
  }
  else if (hpPercent > 0.2f) {
    barColor = {255, 255, 0, alpha};  // Yellow
  }
  else {
    barColor = {255, 0, 0, alpha};    // Red
  }

  SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
  SDL_RenderFillRect(renderer, &rect);
}
#endif //_GAME_CC_