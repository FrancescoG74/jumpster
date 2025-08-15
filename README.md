
# Jumpster

Jumpster is a simple platformer game written in C++ using SDL2, featuring sprite animation.

## Build Instructions

1. Make sure you have installed:
   - SDL2
   - SDL2_image
   - CMake
   - A C++ compiler (g++ recommended)

2. From the project root directory, run:

```sh
mkdir build
cd build
cmake ..
make
./jumpster
```

## Directory Structure

- `src/`         — C++ source code for the game
- `include/`     — C++ header files
- `resources/`   — Images and graphic assets (background, sprites, etc.)
- `build/`       — Build directory (created by CMake)

## Notes
- Images must be placed in the `resources/` folder or referenced as `../resources/` depending on the execution path.
- The hamster is animated using either a 16-frame PNG sprite sheet or 8 separate PNG frames (mario00.png ... mario07.png).
