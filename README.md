# OOP Final Project

This repository holds a C++ console-based strategy game developed as a final project for an Object-Oriented Programming course.

## Current Files & Purpose

- **`Game.cpp`** – Contains the `Game` class implementing the main loop, user interface, and turn processing. It also has the `main()` function that starts the game.
- **`Header.h`** – Single header file declaring all game-related classes (e.g. `Population`, `Military`, `Resources`, etc.).
- **`Implementation.cpp`** – Implements all class methods defined in `Header.h`.
- **`README.md`** – This documentation file.

## How to Build

```bash
# using g++ on Windows (MinGW or similar)
g++ -std=c++17 FileName.cpp Implimentation.cpp -o stronghold
```

Compile both source files and link them together. The executable will be `stronghold.exe` (name is arbitrary).

## Running the Game

Launch the compiled executable and follow the console menu options. Save/load and score logging are performed automatically using `game.txt` and `score.txt`.

## Notable Features

- Modular components representing economy, population, military, leadership, etc.
- Simple save/load system that writes object states to a text file.
- Turn-based mechanics with events, maps, alliances, and trade.

side options, and a helper loop renders them automatically.
- Basic input prompts and error messages are clearer and avoid accidental fall-through.



- Continue improving input validation and centralize error handling
- Add unit tests for core classes (resources, population, economy, etc.)
- Consider using a configuration or macro system for colors/widths
- Add build configuration (Makefile/CMake) for portability

---
This project already demonstrates many OOP principles; the recent refactorings should make further expansion more straightforward.
