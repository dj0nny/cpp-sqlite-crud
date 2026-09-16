#ifndef DB_HPP
#define DB_HPP

#include <SQLiteCpp/SQLiteCpp.h>

#include "Todo.hpp"

void setup_db(SQLite::Database& db);
int64_t insert(SQLite::Database& db);
void select_all(SQLite::Database& db);
void delete_todo(SQLite::Database& db);

#endif