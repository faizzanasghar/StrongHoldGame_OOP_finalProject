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

## Suggested Improvements 🛠️

1. **Separate source files per class** – move each class declaration/definition into its own `.h`/`.cpp` pair for readability and faster compilation. (Already applied; each class now has its own header and implementation.)
2. **Refactor `Game`** – the main loop has been cleaned up using a dedicated `displayMainMenu()` helper, and an `enum class MenuOption` now replaces raw numeric case labels. Missing `break` statements were fixed to prevent fall-through bugs.
3. **Use smart pointers** – all subsystems in `Game` are now managed with `std::unique_ptr`, eliminating manual `new`/`delete` and reducing leak risk.
4. **Improve input validation** – some repeated checks remain, but menu choices use enums and invalid options are handled more uniformly.
5. **Bounds checking on map movement** – the `MapSystem` now prevents moves outside the 5×5 grid and reports an error.
6. **Consistent naming & spelling** – files renamed (`Game.cpp`, `Implementation.cpp`), typos corrected, and a more consistent coding style adopted across headers.
7. **Magic numbers & constants** – resource indices, map dimensions, and menu options use named enums/constexpr values.
8. **Better serialization** – save/load remains text-based but is centralized and easier to modify.
9. **Thread safety & logging** – logger remains simple, but structure allows future extension (e.g., file output or timestamps).
10. **Add unit tests** – still pending; decoupling logic from I/O would make this feasible.

## GUI/UX Improvements 🎨

- Menu drawing is refactored into `displayMainMenu()` with consistent indentation and color management.
- Color codes are defined alongside options, and a helper loop renders them automatically.
- Basic input prompts and error messages are clearer and avoid accidental fall-through.

## Next Steps

- Continue improving input validation and centralize error handling
- Add unit tests for core classes (resources, population, economy, etc.)
- Consider using a configuration or macro system for colors/widths
- Add build configuration (Makefile/CMake) for portability

---
This project already demonstrates many OOP principles; the recent refactorings should make further expansion more straightforward.