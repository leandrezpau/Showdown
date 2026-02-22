

#include "returnPokeData.h"

PokemonData getPokemonById(sqlite3* db, int pokemon_id) {

  const char* sql =
    "SELECT name, primary_type, secondary_type, "
    "attack, defense, special_attack, special_defense, speed, hp, generation, weight, evo_phase, last_evo_phase "
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
    p.weight = sqlite3_column_int(stmt, 10);
    p.evo_phase = sqlite3_column_int(stmt, 11);
    p.last_evo_phase = (bool) sqlite3_column_int(stmt, 12);
  }
  else {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Pokemon no encontrado");
  }

  sqlite3_finalize(stmt);
  return p;
}
MovementData getMoveByName(sqlite3* db, const std::string& moveName)
{
  const char* sql =
    "SELECT ID, Name, Type, Class, Damage, "
    "Secondary_Effect_1, Secondary_Effect_1_chance, "
    "Secondary_Effect_2, Secondary_Effect_2_chance, "
    "Secondary_Effect_3, Secondary_Effect_3_chance, "
    "Secondary_Effect_4, Secondary_Effect_4_chance, "
    "Secondary_Effect_5, Secondary_Effect_5_chance, "
    "Secondary_Effect_6, Secondary_Effect_6_chance, "
    "Accuracy, Target, PP "
    "FROM Moves WHERE Name = ?;";

  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
    return {};
  }

  sqlite3_bind_text(stmt, 1, moveName.c_str(), -1, SQLITE_TRANSIENT);

  MovementData m;

  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    m.id   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    m.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    m.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

    // Convertir Class (string → enum)
    std::string classStr =
      reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    if (classStr == "Physical")      m.moveClass = kClassPhysical;
    else if (classStr == "Special")  m.moveClass = kClassSpecial;
    else                             m.moveClass = kClassStatus;

    m.damage = sqlite3_column_int(stmt, 4);

    m.secondaryEffect1 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    m.secondaryEffect1Chance = sqlite3_column_int(stmt, 6);

    m.secondaryEffect2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
    m.secondaryEffect2Chance = sqlite3_column_int(stmt, 8);

    m.secondaryEffect3 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
    m.secondaryEffect3Chance = sqlite3_column_int(stmt,10);

    m.secondaryEffect4 = reinterpret_cast<const char*>(sqlite3_column_text(stmt,11));
    m.secondaryEffect4Chance = sqlite3_column_int(stmt,12);

    m.secondaryEffect5 = reinterpret_cast<const char*>(sqlite3_column_text(stmt,13));
    m.secondaryEffect5Chance = sqlite3_column_int(stmt,14);

    m.secondaryEffect6 = reinterpret_cast<const char*>(sqlite3_column_text(stmt,15));
    m.secondaryEffect6Chance = sqlite3_column_int(stmt,16);

    m.accuracy = sqlite3_column_int(stmt,17);
    m.target   = reinterpret_cast<const char*>(sqlite3_column_text(stmt,18));
    m.pp       = sqlite3_column_int(stmt,19);
  }
  else
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("Movimiento no encontrado");
  }

  sqlite3_finalize(stmt);
  return m;
}