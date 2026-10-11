# Snake Game in C with SDL2

A classic Snake game written in C using SDL2 graphics library.

## Features

- **Smooth Graphics**: Rendered with SDL2 for responsive gameplay
- **Grid-based Movement**: 20x20 grid with tile-based movement
- **Food Spawning**: Random food placement avoiding snake body
- **Collision Detection**: Wall wrapping and self-collision detection
- **Score Tracking**: Real-time score display
- **Keyboard Controls**: Arrow keys or WASD for movement
- **Game States**: Start, Running, Over screens

## Building

### Prerequisites

- GCC or Clang
- CMake 3.10+
- SDL2 development libraries

### Ubuntu/Debian

```bash
sudo apt-get install libsdl2-dev cmake build-essential
```

### macOS

```bash
brew install sdl2 cmake
```

### Windows (MSVC)

Download SDL2 from https://www.libsdl.org/download-2.0.php and install development libraries.

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
./snake
```

## Controls

| Key | Action |
|-----|--------|
| Arrow Keys / WASD | Move snake |
| SPACE | Start game / Resume after game over |
| R | Reset game |
| Q / ESC | Quit |

## Gameplay

- Move the snake to eat red food squares
- Each food eaten increases score by 10 points
- Snake grows longer with each food
- Avoid hitting yourself
- The snake wraps around screen edges
- Game over when snake collides with itself

## Project Structure

```
├── CMakeLists.txt      # Build configuration
├── src/
│   ├── main.c          # Entry point and game loop
│   ├── game.c/h        # Game logic and state
│   ├── renderer.c/h    # SDL2 rendering
└── README.md
```

## Game Speed

The snake moves every 10 frames (at 60 FPS = 6 moves per second). Adjust the divisor in `game.c` to change difficulty.

## License

MIT License
