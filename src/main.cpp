#include <iostream>
#include <string>
#include <stdexcept>
#include <SQLiteCpp/SQLiteCpp.h>

#include "Todo.hpp"
#include "db.hpp"

int main() {
  try {
    SQLite::Database db = SQLite::Database("todo.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    setup_db(db);

    Todo my_todo {"Clean the house"};

    insert(db, my_todo);

  } catch (std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
  }


  return 0;
}