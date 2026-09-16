#ifndef TODO_HPP
#define TODO_HPP

#include <string>

#include "TodoStatus.hpp"

class Todo {
  private:
    std::string description;
    TodoStatus status;
  
  public:
    Todo(const std::string& todo_description, const TodoStatus todo_status = TodoStatus::NotCompleted);

    std::string get_description() const;

    int get_int_todo_status() const;
};

#endif