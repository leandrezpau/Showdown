

#include "returnPokeData.h"

PokemonData getPokemonById(sqlite3* db, int pokemon_id) {

  const char* sql =
    "SELECT name, primary_type, secondary_type, "
    "attack, defense, special_attack, special_defense, speed, hp, generation "
    "FROM pokemon WHERE id = ?;";

  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
    return {};
  }

  sqlite3_bind_int(stmt, 1, pokemon_id);

  PokemonData p;

  if (sqlite3_step(stmt) == SQLITE_ROW) {

    p.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    p.type1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    p.type2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

    p.attack = sqlite3_column_int(stmt, 3);
    p.defense = sqlite3_column_int(stmt, 4);
    p.specialAttack = sqlite3_column_int(stmt, 5);
    p.specialDefense = sqlite3_column_int(stmt, 6);
    p.speed = sqlite3_column_int(stmt, 7);
    p.hp = sqlite3_column_int(stmt, 8);

    p.maxhp = p.hp;  // Base HP como máximo inicial
    p.generation = sqlite3_column_int(stmt, 9);
  }
  else {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Pokemon no encontrado");
  }

  sqlite3_finalize(stmt);
  return p;
}