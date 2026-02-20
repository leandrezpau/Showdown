#pragma once

#ifndef _BATTLEAI_H
#define _BATTLEAI_H

#include "pokemon.h"
#include "trainer.h"
#include "game.h"

class BattleAI {
public:
  enum Difficulty { EASY = 0, MEDIUM, HARD };

  // Evalua todos los ataques posibles y devuelve un par: {Indice_Del_Mejor_Ataque, Puntuacion_Esperada}
  static std::pair<int, float> ChooseBestMove(Pokemon* aiPokemon, Pokemon* playerPokemon);

  // Evalua todos los cambios de Pokemon posibles y devuelve: {Indice_Del_Mejor_Pokemon, Puntuacion_Esperada}
  // Devuelve -1 en el indice si no hay cambios viables.
  static std::pair<int, float> ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon);

  // Funcion Maestra: Compara el mejor ataque con el mejor cambio y decide que accion final tomar.
  // Devuelve un struct PlayerActions listo para inyectar en el Game Loop.
  static PlayerActions GetBestAction(Trainer* aiTrainer, Pokemon* playerPokemon);

private:
  // Simulador matematico de dano (no modifica el HP real del juego).
  static float PredictDamage(Pokemon* attacker, Pokemon* defender, Movement& move);

  // Funcion Heuristica: Evalua quien tiene la ventaja en el tablero basandose en HP restante y velocidad.
  static float EvaluateBoardState(float aiSimHp, float aiMaxHp, float playerSimHp, float playerMaxHp, bool aiIsFaster);
};

#endif //_BATTLEAI_H