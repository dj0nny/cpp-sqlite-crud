cmake_minimum_required(VERSION 3.20)

project(cpp-sqlite-crud
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SQLITECPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SQLITECPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/SQLiteCpp)

add_executable(cpp-sqlite-crud 
  src/main.cpp
  src/Todo.cpp
  src/utils.cpp
  db/db.cpp
)

target_link_libraries(cpp-sqlite-crud PRIVATE SQLiteCpp)

target_include_directories(cpp-sqlite-crud
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/db
)