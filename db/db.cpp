#include <iostream>

#include "Todo.hpp"
#include "db.hpp"

void setup_db(SQLite::Database& db) {
  SQLite::Transaction init_db_transaction(db);

  db.exec("DROP TABLE IF EXISTS todos");
  db.exec("CREATE TABLE todos ("
    "id INTEGER PRIMARY KEY,"
    "Description varchar(255) NOT NULL,"
    "Status INTEGER DEFAULT 0"
  ")");

  init_db_transaction.commit();
};

int64_t insert(SQLite::Database& db, const Todo& todo) {
  
    SQLite::Statement query(db, "INSERT INTO todos (Description, Status) VALUES (:desc, :status)");

    query.bind(":desc", todo.get_description());
    query.bind(":status", todo.get_int_todo_status());

    query.exec();

    int64_t id {db.getLastInsertRowid()};

    std::cout << "Insert new Todo with ID: " << id << '\n';

    return id;
}