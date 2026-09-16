#include <iostream>
#include <string>
#include <stdexcept>
#include <SQLiteCpp/SQLiteCpp.h>

#include "Todo.hpp"
#include "MenuChoice.hpp"
#include "db.hpp"
#include "utils.hpp"

int main() {
  try {
    SQLite::Database db = SQLite::Database("todo.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    setup_db(db);

    while (true) {
      MenuChoice menu_choice {print_menu()};

      switch (menu_choice) {
        case MenuChoice::Insert:
          insert(db);
          break;
        case MenuChoice::Show:
          select_all(db);
          break;
        case MenuChoice::Delete:
          delete_todo(db);
          break;
        case MenuChoice::Exit:
          return 0;
        default:
          std::cout << "Invalid choice" << '\n';
      }
    
    }

  } catch (std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
  }


  return 0;
}