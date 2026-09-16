#include <iostream>
#include <memory>

#include "Todo.hpp"
#include "TodoStatus.hpp"
#include "db.hpp"
#include "utils.hpp"

void setup_db(SQLite::Database& db) {
  SQLite::Transaction init_db_transaction(db);

  db.exec("CREATE TABLE IF NOT EXISTS todos ("
    "id INTEGER PRIMARY KEY,"
    "Description varchar(255) NOT NULL,"
    "Status INTEGER DEFAULT 0"
  ")");

  init_db_transaction.commit();
};

int64_t insert(SQLite::Database& db) {
  std::unique_ptr<Todo> todo {read_todo()};
  
  SQLite::Statement query(db, "INSERT INTO todos (Description, Status) VALUES (:desc, :status)");
  query.bind(":desc", todo->get_description());
  query.bind(":status", todo->get_int_todo_status());

  query.exec();

  int64_t id {db.getLastInsertRowid()};

  std::cout << "Insert new Todo with ID: " << id << '\n';

  return id;
}

void select_all(SQLite::Database& db) {
  SQLite::Statement query(db, "SELECT * FROM todos");

  while (query.executeStep()) {
    auto id {query.getColumn(0)};
    auto description {query.getColumn(1)};
    int status {query.getColumn(2)};

    std::cout << id << ", " << description << ", " << todo_status_to_string(status) << '\n';
  }
}

void delete_todo(SQLite::Database& db) {
  int todo_id {read_todo_id()};

  SQLite::Statement query(db, "DELETE FROM todos WHERE id = :todoID");

  query.bind(":todoID", todo_id);
  
  if (query.exec() > 0)
    std::cout << "Todo with id " << todo_id << " deleted" << '\n';
  else
    std::cout << "Cannot perform delete, the ID does not exits." << '\n';

}