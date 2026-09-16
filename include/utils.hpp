#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <memory>

#include "TodoStatus.hpp"
#include "Todo.hpp"

void handle_invalid_input(std::istream& is);
int print_menu();
std::string todo_status_to_string(int todo_status);
bool is_valid_todo_status_code(int todo_status_code);

std::unique_ptr<Todo> read_todo();
int read_todo_id();

#endif
