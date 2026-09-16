#include "TodoStatus.hpp"
#include "Todo.hpp"

Todo::Todo(const std::string& todo_description, const TodoStatus todo_status)
    : description {todo_description}, status {todo_status}
  {}

std::string Todo::get_description() const {
  return description;
}

int Todo::get_int_todo_status() const {
  return static_cast<int>(status);
}