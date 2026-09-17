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

void print_single_row(SQLite::Statement& query_result) {
  int column_count {query_result.getColumnCount()};

  for (int i {0}; i < column_count; ++i) {
    if (static_cast<std::string>(query_result.getColumn(i).getName()) != "Status")
      std::cout << query_result.getColumn(i).getText();
    else {
      std::cout << todo_status_to_string(std::stoi(query_result.getColumn(i).getText()));
    }

    if (i != column_count - 1) 
      std::cout << ", ";
  }
  
  std::cout << '\n';
}

void print_multiple_rows(SQLite::Statement& query_result) {
  bool has_rows {false};

  while (query_result.executeStep()) {
    has_rows = true;
    print_single_row(query_result);
  }

  if (!has_rows)
    std::cout << "There are no rows.\n";
}

int64_t insert(SQLite::Database& db) {
  SQLite::Statement query(db, "INSERT INTO todos (Description, Status) VALUES (:desc, :status)");
  
  std::unique_ptr<Todo> todo {read_todo()};
  query.bind(":desc", todo->get_description());
  query.bind(":status", todo->get_int_todo_status());

  query.exec();

  int64_t id {db.getLastInsertRowid()};

  std::cout << "Insert new Todo with ID: " << id << '\n';

  return id;
}

void select_all(SQLite::Database& db) {
  SQLite::Statement query(db, "SELECT * FROM todos");

  print_multiple_rows(query);
}

void select_one(SQLite::Database& db) {
  SQLite::Statement query(db, "SELECT * FROM todos WHERE id = :todoID");
 
  int todo_id {read_todo_id()};

  query.bind(":todoID", todo_id);

  if (query.executeStep()) 
    print_single_row(query);
  else 
    std::cout << "There is not todo with id " << todo_id << '\n';

}

void search_by_description(SQLite::Database& db) {  
  SQLite::Statement query(db, "SELECT * FROM todos WHERE Description LIKE :description");

  std::string description {};
  read_description(description);
  std::string search_pattern {"%" + description + "%"};
  
  query.bind(":description", search_pattern);

  print_multiple_rows(query);
}

void search_by_status(SQLite::Database& db) {
  SQLite::Statement query(db, "SELECT id, Description FROM todos WHERE Status = :todoStatus");

  int todo_status_code {read_status_code()};

  query.bind(":todoStatus", todo_status_code);

  print_multiple_rows(query);
  
}

void delete_todo(SQLite::Database& db) {
  SQLite::Statement query(db, "DELETE FROM todos WHERE id = :todoID");

  int todo_id {read_todo_id()};

  query.bind(":todoID", todo_id);
  
  if (query.exec() > 0)
    std::cout << "Todo with id " << todo_id << " deleted" << '\n';
  else
    std::cout << "Cannot perform delete, the ID does not exits." << '\n';
}