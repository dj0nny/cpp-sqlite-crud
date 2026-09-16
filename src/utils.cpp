#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <memory>

#include "utils.hpp"
#include "Todo.hpp"

void handle_invalid_input(std::istream& is) {
  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Invalid input" << "\n\n";
}

bool is_valid_todo_status_code(int todo_status_code) {
  return todo_status_code == 0 || todo_status_code == 1;
}

int print_menu() {
  std::cout << "\n╔══════════════════════════════════════╗\n";
  std::cout << "║           TODO MANAGER               ║\n";
  std::cout << "║══════════════════════════════════════║\n";
  std::cout << "║ 1. Add todo                          ║\n";
  std::cout << "║ 2. Show todos                        ║\n";
  std::cout << "║ 3. Delete todo by ID                 ║\n";
  std::cout << "║ 0. Exit                              ║\n";
  std::cout << "╚══════════════════════════════════════╝\n\n";

  while (true) {
    std::cout << "Enter an operation: ";
    int choice {};
    std::cin >> choice;

    if (std::cin.fail()) {
      handle_invalid_input(std::cin);
      continue;
    }

    return choice;
  }
}

std::string todo_status_to_string(int todo_status) {
  switch (static_cast<TodoStatus>(todo_status)) {
    case TodoStatus::Completed:
      return "Completed";
    case TodoStatus::NotCompleted:
      return "Not completed";
  }

  throw std::runtime_error("Invalid todo status");
}

std::unique_ptr<Todo> read_todo() {
  std::cout << "Enter todo description: ";
  std::string description {};
  std::getline(std::cin >> std::ws, description);

  while (true) {
    std::cout << "Enter todo status (0 = not completed, 1 = completed): ";
    int todo_status_code {};
    std::cin >> todo_status_code;

    if (std::cin.fail()) {
      handle_invalid_input(std::cin);
      continue;
    }

    if (!is_valid_todo_status_code(todo_status_code)) {
      std::cout << "Invalid status code" << '\n';
      continue;
    }

    return std::make_unique<Todo>(description, static_cast<TodoStatus>(todo_status_code));

  }
}

int read_todo_id() {
  while (true) {
    std::cout << "Enter todo ID: ";
    int todo_id {};
    std::cin >> todo_id;

    if (std::cin.fail()) {
      handle_invalid_input(std::cin);
      continue;
    }

    return todo_id;
  }
}