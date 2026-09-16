#ifndef DB_HPP
#define DB_HPP

#include <SQLiteCpp/SQLiteCpp.h>

#include "Todo.hpp"

void setup_db(SQLite::Database& db);
int64_t insert(SQLite::Database& db, const Todo& todo);

#endif