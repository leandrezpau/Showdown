

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
  std::string queryString;
  
  // Si moveName está vacío, seleccionamos uno al azar
  if (moveName.empty()) {
    queryString = 
      "SELECT ID, Name, Type, Class, Damage, "
      "Secondary_Effect_1, Secondary_Effect_1_chance, "
      "Secondary_Effect_2, Secondary_Effect_2_chance, "
      "Secondary_Effect_3, Secondary_Effect_3_chance, "
      "Secondary_Effect_4, Secondary_Effect_4_chance, "
      "Secondary_Effect_5, Secondary_Effect_5_chance, "
      "Secondary_Effect_6, Secondary_Effect_6_chance, "
      "Accuracy, Target, PP "
      "FROM Moves ORDER BY RANDOM() LIMIT 1;";
  } else {
    queryString = 
      "SELECT ID, Name, Type, Class, Damage, "
      "Secondary_Effect_1, Secondary_Effect_1_chance, "
      "Secondary_Effect_2, Secondary_Effect_2_chance, "
      "Secondary_Effect_3, Secondary_Effect_3_chance, "
      "Secondary_Effect_4, Secondary_Effect_4_chance, "
      "Secondary_Effect_5, Secondary_Effect_5_chance, "
      "Secondary_Effect_6, Secondary_Effect_6_chance, "
      "Accuracy, Target, PP "
      "FROM Moves WHERE Name = ?;";
  }

  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, queryString.c_str(), -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "SQL ERROR: " << sqlite3_errmsg(db) << std::endl;
    return {};
  }

  // Solo vinculamos el parámetro si estamos buscando por nombre
  if (!moveName.empty()) {
    sqlite3_bind_text(stmt, 1, moveName.c_str(), -1, SQLITE_TRANSIENT);
  }

  MovementData m;

  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    // Función auxiliar para manejar punteros nulos de SQLite de forma segura
    auto safe_column_text = [&](int col) -> const char* {
        const unsigned char* text = sqlite3_column_text(stmt, col);
        return text ? reinterpret_cast<const char*>(text) : "";
    };

    m.id   = safe_column_text(0);
    m.name = safe_column_text(1);
    m.type = safe_column_text(2);

    std::string classStr = safe_column_text(3);
    if (classStr == "1")      m.moveClass = kClassPhysical;
    else if (classStr == "2") m.moveClass = kClassSpecial;
    else                      m.moveClass = kClassStatus;

    m.damage = sqlite3_column_int(stmt, 4);

    m.secondaryEffect1 = safe_column_text(5);
    m.secondaryEffect1Chance = sqlite3_column_int(stmt, 6);

    m.secondaryEffect2 = safe_column_text(7);
    m.secondaryEffect2Chance = sqlite3_column_int(stmt, 8);

    m.secondaryEffect3 = safe_column_text(9);
    m.secondaryEffect3Chance = sqlite3_column_int(stmt, 10);

    m.secondaryEffect4 = safe_column_text(11);
    m.secondaryEffect4Chance = sqlite3_column_int(stmt, 12);

    m.secondaryEffect5 = safe_column_text(13);
    m.secondaryEffect5Chance = sqlite3_column_int(stmt, 14);

    m.secondaryEffect6 = safe_column_text(15);
    m.secondaryEffect6Chance = sqlite3_column_int(stmt, 16);

    m.accuracy = sqlite3_column_int(stmt, 17);
    m.target   = safe_column_text(18);
    m.pp       = sqlite3_column_int(stmt, 19);
  }
  else
  {
    sqlite3_finalize(stmt);
    throw std::runtime_error("No se pudo obtener el movimiento (BD vacía o nombre inexistente)");
  }

  sqlite3_finalize(stmt);
  return m;
}