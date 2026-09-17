#ifndef DB_HPP
#define DB_HPP

#include <SQLiteCpp/SQLiteCpp.h>

#include "Todo.hpp"

void setup_db(SQLite::Database& db);
int64_t insert(SQLite::Database& db);
void select_all(SQLite::Database& db);
void select_one(SQLite::Database& db);
void search_by_description(SQLite::Database& db);
void search_by_status(SQLite::Database& db);
void delete_todo(SQLite::Database& db);

void print_single_row(const SQLite::Statement& query_result);
void print_multiple_rows(SQLite::Statement& query_result);

#endif