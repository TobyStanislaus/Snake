# Snake

A C++ implementation of the classic **Snake** game, played entirely in the terminal.

The project was built to practise fundamental C++ programming concepts through a simple interactive game, including classes, vectors, keyboard input, game-state management, collision detection, and real-time updates.

## Features

* Classic Snake gameplay
* Terminal-based rendering
* Real-time movement
* Keyboard controls
* Food generation
* Snake growth
* Score tracking
* Self-collision detection
* Boundary collision detection
* Increasing difficulty as the snake grows

## Controls

| Key | Action     |
| --- | ---------- |
| `W` | Move up    |
| `A` | Move left  |
| `S` | Move down  |
| `D` | Move right |

## How It Works

The game runs through a continuous game loop:

```text
        ┌─────────────┐
        │ Read Input  │
        └──────┬──────┘
               │
               ▼
        ┌─────────────┐
        │ Move Snake  │
        └──────┬──────┘
               │
               ▼
        ┌─────────────┐
        │ Check       │
        │ Collisions  │
        └──────┬──────┘
               │
               ▼
        ┌─────────────┐
        │ Check Food  │
        └──────┬──────┘
               │
               ▼
        ┌─────────────┐
        │ Render      │
        │ Terminal    │
        └──────┬──────┘
               │
               └──────────► Repeat
```

The terminal is repeatedly redrawn to give the appearance of continuous movement.

## Snake Representation

The snake's body is represented as a collection of positions.

Each segment has a position on the game board, with the first element representing the snake's head.

When the snake moves:

1. A new head position is calculated.
2. The new head is added to the front of the snake.
3. The final segment is removed.
4. If food was collected, the final segment is retained, causing the snake to grow.

This provides a simple way to model the movement of the entire snake without individually calculating the movement of every segment.

## Food

Food is generated at a random position on the game board.

When the snake's head reaches the food:

* The score increases.
* The snake grows.
* A new food position is generated.

The food position is checked against the snake so that it does not spawn inside the snake's body.

## Collision Detection

The game checks for several types of collision.

### Boundary Collision

The game ends if the snake's head moves outside the playable area.

### Self Collision

The snake's head is compared with the positions of the remaining body segments.

If the head occupies the same position as any part of the body, the game ends.

### Food Collision

If the head occupies the same position as the food, the snake grows and the score is increased.

## Terminal Rendering

Instead of using a graphics library, the game uses standard terminal output to represent the game board.

A typical frame consists of:

```text
+--------------------+
|                    |
|       ####         |
|          O         |
|                    |
|             *      |
|                    |
+--------------------+

Score: 5
```

The terminal is cleared and redrawn as the game state changes.

This keeps the project lightweight while still requiring the implementation of a real-time update loop.

## Technologies

* **C++**
* Standard C++ Library
* Terminal/console I/O
* Object-oriented programming
* `std::vector`
* Random number generation

## Building and Running

### Requirements

* A C++ compiler
* A terminal capable of displaying the game's characters

### Compile

Using `g++`:

```bash
g++ *.cpp -o Snake
```

### Run

On Windows:

```bash
Snake.exe
```

On Linux/macOS:

```bash
./Snake
```

## Project Structure

```text
Snake/
├── ...
├── LICENSE
└── README.md
```

## What I Learned

This project provided practice with fundamental C++ programming concepts, including:

* Classes and object-oriented design
* `std::vector` and dynamic collections
* References and pointers
* Functions and program decomposition
* Terminal input/output
* Random number generation
* Collision detection
* Managing changing game state
* Implementing a real-time game loop
* Debugging state-dependent behaviour

## Future Improvements

Possible extensions include:

* Increasing the game speed as the score increases
* High-score persistence
* Pause functionality
* Improved terminal graphics
* Multiple difficulty levels
* Additional game modes
* Configurable board sizes
* A graphical version using SFML
* CMake-based build configuration

## License

This project is licensed under the terms specified in [`LICENSE`](LICENSE).
