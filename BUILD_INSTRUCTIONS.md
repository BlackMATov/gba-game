# Build Instructions

## * Requirements

- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [devkitPro](https://devkitpro.org/wiki/devkitPro_pacman)

## * Cloning

```bash
$ git clone git://github.com/BlackMATov/gba-game.git
$ cd gba-game
```

## * Building

```bash
$ cd your_game_repository_directory
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
```

## * Running

- Game Boy Advance emulator ([mGBA](https://mgba.io/) for example)

```bash
$ cd your_game_build_directory
$ mgba game/gba-game.gba
```

## * Links

- CMake: https://cmake.org/
- devkitPro: https://devkitpro.org/
- mGBA: https://mgba.io/
