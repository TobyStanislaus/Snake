# Snake

A C++ implementation of the classic **Snake** game, built using **SFML**.

The project was developed to practise object-oriented C++ programming and real-time game development, including game loops, keyboard input, movement, collision detection, dynamic data structures, and graphical rendering.

## Features

* Classic Snake gameplay
* Real-time keyboard controls
* Snake grows when food is collected
* Randomly positioned food
* Self-collision detection
* Screen boundary collision
* Score tracking
* Increasing snake length
* Real-time rendering using SFML

## Controls

| Key | Action     |
| --- | ---------- |
| `↑` | Move up    |
| `↓` | Move down  |
| `←` | Move left  |
| `→` | Move right |

## How It Works

The game operates using a continuous update-and-render loop:

```text
Input
  │
  ▼
Update Direction
  │
  ▼
Move Snake
  │
  ├── Check Food
  │
  ├── Check Self Collision
  │
  └── Check Boundaries
  │
  ▼
Update Game State
  │
  ▼
Render
  │
  └──────► Repeat
```

The snake is represented as a collection of segments. During each movement update, a new head position is calculated based on the current direction and the rest of the body follows the previous positions.

## Movement

The snake moves continuously in one of four directions.

Rather than allowing arbitrary movement, the game restricts the snake to horizontal and vertical movement:

```text
       ↑
       │
←──── S ────→
       │
       ↓
```

The direction can be changed using the arrow keys, while preventing the snake from immediately reversing direction into itself.

## Snake Growth

When the snake reaches the food, its length increases.

The basic gameplay loop is:

```text
        ┌──────────────┐
        │ Move Snake   │
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │ Food eaten?  │
        └──────┬───────┘
          Yes  │  No
               │
       ┌───────▼───────┐
       │ Increase      │
       │ snake length  │
       └───────┬───────┘
               │
               ▼
        Spawn new food
```

This creates the central progression mechanic of Snake: the longer the snake becomes, the more difficult it is to avoid collisions.

## Collision Detection

The game checks the snake's position against the objects and boundaries of the game world.

Collision checks include:

* Snake head vs. food
* Snake head vs. its own body
* Snake head vs. the edge of the game area

Self-collision becomes increasingly important as the snake grows, since the available space decreases while the number of occupied positions increases.

## Game Loop

SFML provides the window, event handling, rendering and timing functionality required by the game.

Each iteration of the main loop handles three main stages:

### 1. Input

SFML events and keyboard state are used to determine whether the player has changed direction.

### 2. Update

The game state is updated based on the current direction and elapsed time.

This includes:

* Moving the snake
* Checking for food
* Growing the snake
* Checking collisions
* Updating the score

### 3. Rendering

The current state of the game is drawn to the SFML window.

This separation between **input, game state updates and rendering** is a fundamental pattern used in real-time applications and game engines.

## Technologies

* **C++**
* **SFML**
* Standard C++ Library
* Object-oriented programming
* 2D game development
* Real-time input handling
* Collision detection

## Building and Running

### Requirements

* A C++ compiler
* SFML
* A configured C++ development environment

SFML provides cross-platform windowing and graphics functionality for C++ applications.

### Clone

```bash
git clone https://github.com/TobyStanislaus/Snake.git
cd Snake
```

Configure SFML with your compiler and build the project.

After compilation, run the generated executable.

## Project Structure

```text
Snake/
├── main.cpp
├── Snake.cpp
├── Snake.hpp
├── Food.cpp
├── Food.hpp
├── ...
├── LICENSE
└── README.md
```

## What I Learned

This project was an early application of C++ to real-time graphical programming.

It provided practice with:

* Object-oriented C++ design
* Classes and encapsulation
* Header and implementation files
* SFML graphics and event handling
* Real-time game loops
* Keyboard input
* 2D coordinate systems
* Collision detection
* Dynamic data structures
* Random number generation
* Managing changing game state

## Future Improvements

Possible extensions include:

* Increasing difficulty as the score increases
* High-score persistence
* Pause and resume functionality
* Start and game-over menus
* Sound effects
* Improved graphical effects
* Configurable game speed
* Multiple game modes
* A grid-based movement system
* CMake-based project configuration
* Current bug where if you go down, then back on yourself quickly you can run into yourself

## License

This project is licensed under the terms specified in [`LICENSE`](LICENSE).
