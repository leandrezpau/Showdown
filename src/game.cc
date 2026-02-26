#define _GAME_CC_
#ifdef _GAME_CC_
#include "game.h"
#include "battleai.h"
#include <iostream>
SDL_Color GetHPBarColor(Pokemon poke, unsigned char alpha){
  float hp = poke.currentStats.HP;
  float maxHp = poke.currentStats.maxHP;

  float hpPercent = hp / maxHp;

  // Cambiar color según porcentaje
  if (hpPercent > 0.5f) {
    return {0, 255, 0, alpha};    // Green
  }
  else if (hpPercent > 0.2f) {
    return {255, 255, 0, alpha};  // Yellow
  }
  else {
    return {255, 0, 0, alpha};    // Red
  }
}

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

  SetTexts();

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
                SetTexts();
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
      SetTexts();
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
    GetNewPP();
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
          SDL_FRect dstName = {
            70.0f + 190.0f * row + 54,
            385.0f + 16 + jump,
            (float)pokeNameText[i][0].w,
            (float)pokeNameText[i][0].h
          };
          SDL_RenderTexture(renderer, pokeNameText[i][0].texture, NULL, &dstName);
          SDL_FRect rect = {
            70.0f + row * 190.0f + 74, 
            385.0f + 48 + jump, 
            (100 * (trainer1->team[i].currentStats.HP / trainer1->team[i].currentStats.maxHP)), 
            8};
          SDL_Color barColor = GetHPBarColor(trainer1->team[i], 80);
          SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
          SDL_RenderFillRect(renderer, &rect);
        }
      }
      break;
    }
    case kActionChangePoke:{
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
        SDL_FRect dstName = {
          70.0f + 190.0f * row + 54,
          385.0f + 16 + jump,
          (float)pokeNameText[i][0].w,
          (float)pokeNameText[i][0].h
        };
        SDL_RenderTexture(renderer, pokeNameText[i][0].texture, NULL, &dstName);
        SDL_FRect rect = {
          70.0f + row * 190.0f + 74, 
          385.0f + 48 + jump, 
          (100 * (trainer1->team[i].currentStats.HP / trainer1->team[i].currentStats.maxHP)), 
          8};
        SDL_Color barColor = GetHPBarColor(trainer1->team[i], 80);
        SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
        SDL_RenderFillRect(renderer, &rect);
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
          SDL_FRect dstName = {
            210.0f + 216.0f * i,
            382.0f + 78.0f * e,
            (float)movementTexts[index][0].w,
            (float)movementTexts[index][0].h
          };
          SDL_FRect dstPP = {
            210.0f + 216.0f * i,
            420.0f + 78.0f * e,
            (float)movementTexts[index][1].w,
            (float)movementTexts[index][1].h
          };
          // Movement Name
          SDL_RenderTexture(renderer, movementTexts[index][0].texture, NULL, &dstName);
          // Movement PP
          SDL_RenderTexture(renderer, movementTexts[index][1].texture, NULL, &dstPP);
        } 
      }
      break;
    }
  }
  // Normal HUD -> Player HP & Enemy HP
  SDL_FRect dstName = { 419, 235,
    (float) pokeNameText[trainer1->currentPokemonIndex][0].w,
    (float) pokeNameText[trainer1->currentPokemonIndex][0].h
  };
  SDL_RenderTexture(renderer, pokeNameText[trainer1->currentPokemonIndex][0].texture, NULL, &dstName);
  float barLenght = 96 * (trainer1->team[trainer1->currentPokemonIndex].currentStats.HP / trainer1->team[trainer1->currentPokemonIndex].currentStats.maxHP);
  SDL_FRect rect = { 512, 262, barLenght, 4};
  SDL_Color barColor = GetHPBarColor(trainer1->team[trainer1->currentPokemonIndex], 200);
  SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
  SDL_RenderFillRect(renderer, &rect);

  SDL_FRect dstNameEnemy = { 60, 32,
    (float) pokeNameText[trainer2->currentPokemonIndex][1].w,
    (float) pokeNameText[trainer2->currentPokemonIndex][1].h
  };
  SDL_RenderTexture(renderer, pokeNameText[trainer2->currentPokemonIndex][1].texture, NULL, &dstNameEnemy);
  float barLenght2 = 96 * (trainer2->team[trainer2->currentPokemonIndex].currentStats.HP / trainer2->team[trainer2->currentPokemonIndex].currentStats.maxHP);
  SDL_FRect rect2 = { 88, 60, barLenght2, 4};
  barColor = GetHPBarColor(trainer2->team[trainer2->currentPokemonIndex], 200);
  SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
  SDL_RenderFillRect(renderer, &rect2);

}
void Game::ResetAction(){
  for(int i = 0; i < 2; i++){
    playerActions.playerAction[i] = kActionNULL;
    playerActions.playerIndex[i] = 0;
    playerActions.decided[i] = false;
  }

  std::cout << "\nPress 1 to attack\nPress 2 to change pokemon";
}

Text Game::CreateText(SDL_Renderer* renderer, TTF_Font* font, const std::string& str, SDL_Color color) {
  Text t;
  SDL_Surface* surface =
      TTF_RenderText_Blended(font, str.c_str(), str.size(), color);

  if (!surface) return t;

  t.texture = SDL_CreateTextureFromSurface(renderer, surface);
  t.w = surface->w;
  t.h = surface->h;

  SDL_DestroySurface(surface);

  return t;
}
void Game::SetTexts(){
  for(int f = 0; f < 2; f++){
    int kNumPoke = (f == 0) ? trainer1->team.size() : trainer2->team.size();
    for (int i = 0; i < kNumPoke; i++) {
      char textString[50];
      if (f == 0) {
        snprintf(textString, 50, "%s", trainer1->team[i].name.c_str());
      } else {
        snprintf(textString, 50, "%s", trainer2->team[i].name.c_str());
      }
      

      int e = 1;
      while(textString[e] != '\0') {
        textString[e] = std::tolower(textString[e]);
        e++;
      }

      pokeNameText[i][f] = CreateText(
        renderer,
        font,
        textString,
        {168, 184, 184, 255}
      );
    }
  }
  for (int i = 0; i < trainer1->team[trainer1->currentPokemonIndex].movement.size(); i++) {
    for(int e = 0; e < 2; e++){
      char textString[50];
      if(e == 0){
        snprintf(textString, 50, "%s", trainer1->team[trainer1->currentPokemonIndex].movement[i].moveName.c_str());
      }else{
        snprintf(textString, 50, "%d/%d", trainer1->team[trainer1->currentPokemonIndex].movement[i].currentPP, trainer1->team[trainer1->currentPokemonIndex].movement[i].pp);
      }
      
      movementTexts[i][e] = CreateText(
        renderer,
        font,
        textString,
        {168, 184, 184, 255}
      );
    }
  }
}
void Game::GetNewPP(){
  for(int i = 0; i < trainer1->team[trainer1->currentPokemonIndex].movement.size(); i++){
    char textString[50];
    snprintf(textString, 50, "%d/%d", trainer1->team[trainer1->currentPokemonIndex].movement[i].currentPP, trainer1->team[trainer1->currentPokemonIndex].movement[i].pp);
    movementTexts[i][1] = CreateText(
      renderer,
      font,
      textString,
      {168, 184, 184, 255}
    );
  }
}

#endif //_GAME_CC_