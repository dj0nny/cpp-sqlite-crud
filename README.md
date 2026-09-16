# cpp-sqlite-crud

A command-line todo manager written in C++ w/ SQLiteCpp.

The application uses SQLite as a persistent database for storing the data.

---

## Technologies

* C++
* SQLite
* SQLiteCpp
* CMake

---

## Requirements

* C++17 or later
* CMake
* A compatible C++ compiler
* SQLite3

---

## Build

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

---

## Run

Git Bash:

```bash
./build/cpp-sqlite-crud.exe
```

PowerShell:

```powershell
.\build\cpp-sqlite-crud.exe
```