#define _GAME_CC_
#ifdef _GAME_CC_
#include "game.h"
#include "battleai.h"
#include <iostream>

using namespace std;

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
  cout << "\n" << _trainer1->name << "you are being challenged by " << _trainer2->name;

  trainer1 = _trainer1;
  trainer2 = _trainer2;

  HealPlayer(trainer1);
  HealPlayer(trainer2);

  ResetAction();

  fightManager = kFightWaitingChoice;
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
      cout << "\n" << trainer2->name << " (IA) esta decidiendo su jugada...\n";

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
      if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        switch(playerActions.playerAction[0]){
          case kActionNULL:{
            int index = SelectBattleAction(event);
            // When pokemon is Fainted, to select new poke
            if(index != -1){
              if (trainer1->GetCurrentPokemon().currentStats.HP <= 0){
                if (index < trainer1->team.size() && trainer1->team[index].currentStats.HP > 0) {
                  trainer1->currentPokemonIndex = index;
                  fightManager = kFightWaitingChoice;
                  cout << "\n" << trainer1->name << " envia a " << trainer1->team[index].name << "!";
                }
                else {
                  cout << "\nEse Pokemon no es valido o esta debilitado. Elige otro.";
                }
              }else{
                if(index >= 1 || index <= 2){
                  playerActions.playerAction[0] = (en_Actions) index;
                }
              }
            }
            break;
          }
          case kActionChangePoke:{
            // When Changing pokemon
            int index = SelectBattleAction(event);
            if(index != -1){
              playerActions.playerIndex[0] = index;
              if(ValidateAction(playerActions)){
                fightManager = kFightPlayingChoice;
                return;
              }else{
                playerActions.playerIndex[0] = 0;
                
              }
            }
            break;
          }
          case kActionAttack:{
            // When selecting which movement to use
            int index = SelectBattleAction(event);
            if(index != -1){
              Pokemon poke = trainer1->GetCurrentPokemon();
              if (playerActions.playerAction[0] == kActionAttack) {
                playerActions.playerIndex[0] = index;
                if (ValidateAction(playerActions)) {
                  fightManager = kFightPlayingChoice;
                  return;
                } else {
                  playerActions.playerIndex[0] = 0;
                }
              }
            }
            break;
          }
        }
      }
      if(event.key.scancode == SDL_SCANCODE_ESCAPE){
        ResetAction();
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
        cout << "\nYour poke does't have a move in that slot";
        break;
      }else{
        if(poke.movement[act_.playerIndex[0]].currentPP <= 0){
          isValid = false;
          cout << "\nThat Movement doesn't have PP";
          break;
        }
      }
      break;
    }
    //IF PLAYER WANTS TO CHOOSE POKEMON
    case kActionChangePoke:{
      if(trainer1->team.size() < act_.playerIndex[0] + 1){
        isValid = false;
        cout << "\nYou don't have pokemon in that slot";
        break;
      }else{
        if(trainer1->team[act_.playerIndex[0]].currentStats.HP <= 0){
          isValid = false;
          cout << "\nThat poke is fainted";
          break;
        }
      }
      break;
    }
    //IF ACTION WAS NULL (SOMETHING CRASHED)
    case kActionNULL:{
      cout << "\nNo action played";
      break;
    }
  }
  playerActions.decided[0] = isValid;
  return isValid;
}

// Motor de Ejecucion: Procesa las acciones elegidas respetando el sistema de prioridades de Pokemon
void Game::PlayActions() {
  if(playerActions.decided[0] == true){
    cout << "\n\n--- COMIENZA EL TURNO ---";

    Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
    Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

    // === PRIORIDAD 1: CAMBIOS DE POKEMON ===
    // Los cambios siempre ocurren antes que cualquier ataque
    if (playerActions.playerAction[0] == kActionChangePoke) {
      trainer1->currentPokemonIndex = playerActions.playerIndex[0];
      p1 = &trainer1->team[trainer1->currentPokemonIndex];
      cout << "\n" << trainer1->name << " retiro a su Pokemon y envio a " << p1->name << "!";
    }

    if (playerActions.playerAction[1] == kActionChangePoke) {
      trainer2->currentPokemonIndex = playerActions.playerIndex[1];
      p2 = &trainer2->team[trainer2->currentPokemonIndex];
      cout << "\n" << trainer2->name << " retiro a su Pokemon y envio a " << p2->name << "!";
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
        if (move.currentPP > 0){
          move.currentPP--;
          attacker->UseMove(*defender, move);
          cout << "Finalizado ataque de " << attacker->name << " a " << defender->name;
        }
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

    fightManager = kFightResults;
  }
}

// Fase Final del Turno: Revisa caidos y fuerza la entrada de nuevos Pokemon al campo
void Game::ResultFromActions() {
  if(playerActions.decided[0] == true){
    cout << "\n\n--- RESOLUCION DEL TURNO ---";

    Pokemon* p1 = &trainer1->team[trainer1->currentPokemonIndex];
    Pokemon* p2 = &trainer2->team[trainer2->currentPokemonIndex];

    // Comprueba si el Pokemon del JUGADOR 1 se ha desmayado
    if (p1->currentStats.HP <= 0 && p1->state != kStateFainted) {
      p1->currentStats.HP = 0;
      p1->state = kStateFainted;
      cout << "\n!" << p1->name << " de " << trainer1->name << " se ha debilitado!";

      // Si le quedan Pokemon vivos, forzamos un cambio via consola/SDL
      if (trainer1->HasAvailablePokemon()) {
        bool choosing = true;
        cout << "\nElige a tu proximo Pokemon (1 - " << trainer1->team.size() << "): ";
      }
    }

    // Comprueba si el Pokemon del JUGADOR 2 (IA) se ha desmayado
    if (p2->currentStats.HP <= 0 && p2->state != kStateFainted) {
      p2->currentStats.HP = 0;
      p2->state = kStateFainted;
      cout << "\n!" << p2->name << " de " << trainer2->name << " se ha debilitado!";

      if (trainer2->HasAvailablePokemon()) {
        if (trainer2->isAI) {
          // La IA elige automaticamente a su mejor opcion de reserva
          Pokemon* currentP1 = &trainer1->team[trainer1->currentPokemonIndex];
          pair<int, float> aiSwitch = BattleAI::ChooseSwitch(trainer2, currentP1);

          if (aiSwitch.first != -1) {
            trainer2->currentPokemonIndex = aiSwitch.first;
            cout << "\n" << trainer2->name << " envia a " << trainer2->team[trainer2->currentPokemonIndex].name << "!";
          }
        }
      }
    }
    ResetAction();
    fightManager = kFightWaitingChoice;
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
        DrawSelectPokemon();
      }else{
        DrawText("Attack",          100, 433, true);
        DrawText("Change Pokemon",  379, 433, true);
      }
      break;
    }
    case kActionChangePoke:{
      DrawSelectPokemon();
      break;
    }
    case kActionAttack:{
      // Movements rectangles & text
      for(int i = 0; i < 2; i++){
        for(int e = 0; e < 2; e++){
          int index = i + e * 2;
          // Rectangle Colors For Movements
          DrawMovement(trainer1->GetCurrentPokemon().movement[index], 208.0f + 216.0f * i, 380.0f + 78.0f * e, false);
        }
      }
      break;
    }
  }
  // USER HUD
  // User Pokemon Name
  DrawText(trainer1->GetCurrentPokemon().name, 419, 235, true);
  // Current HP / Max HP un the HUD
  char hpText[10];
  snprintf(hpText, 10, "%.0f", trainer1->GetCurrentPokemon().currentStats.HP);
  DrawText(hpText, 537, 272, true, 1.5);

  snprintf(hpText, 10, "%.0f", trainer1->GetCurrentPokemon().currentStats.maxHP);
  DrawText(hpText, 574, 272, true, 1.5);
  // User Life Green bar
  DrawLifeBar(trainer1->GetCurrentPokemon().currentStats, 512, 262, 96, 4, 200);

  // ENEMY HUD
  // Enemy Pokemon Name
  DrawText(trainer2->GetCurrentPokemon().name, 60, 32, true);
  // Enemy Life Bar
  DrawLifeBar(trainer2->GetCurrentPokemon().currentStats, 88, 60, 96, 4, 200);
}
void Game::ResetAction(){
  for(int i = 0; i < 2; i++){
    playerActions.playerAction[i] = kActionNULL;
    playerActions.playerIndex[i] = 0;
    playerActions.decided[i] = false;
  }
}
void Game::DrawText(const string& str, float posX, float posY, bool loweredText, float scale, SDL_Color color){
  string pokeName = str;
  scale = scale / 2;

  if(loweredText && pokeName.size() >= 1){
    for(int i = 1; i < pokeName.size(); i++){
      pokeName[i] = tolower(pokeName[i]);
    }
  }
  SDL_Surface* surface = TTF_RenderText_Solid(font, pokeName.c_str(), pokeName.size(), color);

  if (!surface) return;

  SDL_Texture* textToDraw = SDL_CreateTextureFromSurface(renderer, surface);
  
  SDL_FRect dstText = { 
    posX + (2 * scale), 
    posY,
    (float) surface->w * scale,
    (float) surface->h * scale
  };


  // Shadow behind real text
  SDL_RenderTexture(renderer, textToDraw, NULL, &dstText);
  dstText.x -= (2 * scale);
  dstText.y += (2 * scale);
  SDL_RenderTexture(renderer, textToDraw, NULL, &dstText);
  dstText.x += (2 * scale);
  SDL_RenderTexture(renderer, textToDraw, NULL, &dstText);

  // Real Text
  dstText.x -= (2 * scale);
  dstText.y -= (2 * scale);
  SDL_SetTextureColorMod(textToDraw, 133, 122, 111);
  SDL_RenderTexture(renderer, textToDraw, NULL, &dstText);

  // Destroying every allocation
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(textToDraw);
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
    if(alpha == 80) alpha = 200;
    barColor = {255, 255, 0, alpha};  // Yellow
  }
  else {
    if(alpha == 80) alpha = 200;
    barColor = {255, 0, 0, alpha};    // Red
  }

  SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void Game::DrawMovement(Movement move, float posX, float posY, bool drawType){
  // Rectangle Colors For Movements
  SDL_FRect rect = { posX, posY, 216.0f, 78.0f };
  float color = (float) move.moveType.type / 18 * 255;
  SDL_SetRenderDrawColor(renderer, color, color, color, 255);
  SDL_RenderFillRect(renderer, &rect);

  // Movements text
  DrawText(move.moveName, posX + 2, posY + 2, true);
  // Movement PP Text
  char ppText[10];
  snprintf(ppText, 10, "%d/%d", move.currentPP, move.pp);
  DrawText(ppText, posX + 2, posY + 40, true);

  SDL_FRect iconDst = { posX + 77, posY + 40, 64.0f, 24.0f};
  move.moveType.typeIcons_s[(int) move.moveType.type].DrawSprite(150, iconDst);
}

void Game::DrawSelectPokemon(){
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
int Game::SelectBattleAction(SDL_Event event_){
  auto WhichPokemon = [](float x_, float y_, Trainer trainer){
    if(y_ >= 380){
      for(int i = 0; i < trainer.team.size(); i++){
        int jump = (i >= 3) ? 70 : 0;
        int row = i % 3;
        SDL_FRect barDst = {
          70.0f + row * 190.0f, 
          385.0f + jump, 
          189.0f, 69.0f
        };
        if (x_ >= barDst.x && 
            y_ >= barDst.y && 
            x_ <= barDst.x + barDst.w && 
            y_ <= barDst.y + barDst.h)
        {
          return i;
        }
      }
    }
    return -1;
  };
  auto WhichMovement = [](float x_, float y_, Pokemon poke){
    if(y_ >= 380){
      for(int i = 0; i < 2; i++){
        for(int e = 0; e < 2; e++){
          int index = i + e * 2;
          // Coords of the movement rectangle
          SDL_FRect rect = {  208.0f + 216.0f * i, 
                              380.0f + 78.0f * e, 
                              216.0f + 208.0f + 216.0f * i, 
                              78.0f  + 380.0f + 78.0f * e};
          if (x_ >= rect.x && 
              y_ >= rect.y && 
              x_ <= rect.w && 
              y_ <= rect.h)
          {
            return index;
          }
        }
      }
    }
    return -1;
  };
  auto WhichAction = [](float x_, float y_){
    if(y_ >= 380){
      if (x_ >= 0 && 
          y_ >= 320 && 
          x_ <= 268 && 
          y_ <= 535)
      {
        return 1;
      }
      if (x_ >= 268 && 
          y_ >= 320 && 
          x_ <= 640 && 
          y_ <= 535)
      {
        return 2;
      }
    }
    return -1;
  };

  if (event_.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    int x = event_.button.x;
    int y = event_.button.y;
    int button = event_.button.button;

    if (button == SDL_BUTTON_LEFT) {
      switch(fightManager){
        case kFightInit:{
          break;
        }
        case kFightWaitingChoice:{
          switch(playerActions.playerAction[0]){
            case kActionNULL:{
              if (trainer1->GetCurrentPokemon().currentStats.HP <= 0){
                return WhichPokemon((float) x, (float) y, *trainer1);
              }else{
                return WhichAction((float) x, (float) y);
              }
              break;
            }
            case kActionAttack:{
              return WhichMovement((float) x, (float) y, trainer1->GetCurrentPokemon());
              break;
            }
            case kActionChangePoke:{
              return WhichPokemon((float) x, (float) y, *trainer1);
              break;
            }
          }
          break;
        }
        case kFightPlayingChoice:{
          break;
        }
        case kFightResults:{
          break;
        }
        case kFightEnd:{
          break;
        }
      }
      printf("Click izquierdo en (%d, %d)\n", x, y);
    }
  }
  return -1;
}

int ClickedHere(SDL_FRect rectangle, SDL_Event click){
  if (click.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    int x_ = click.button.x;
    int y_ = click.button.y;
    int button = click.button.button;

    if (button == SDL_BUTTON_LEFT) {
      if (x_ >= rectangle.x && 
          y_ >= rectangle.y && 
          x_ <= rectangle.x + rectangle.w && 
          y_ <= rectangle.x + rectangle.h)
      {
        return 1;
      } else {
        return 0;
      }
    }
  }
  return 0;
}
#endif //_GAME_CC_