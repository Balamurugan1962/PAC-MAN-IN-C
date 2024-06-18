# Pac-Man Project in C

## Introduction

The Pac-Man project is a recreation of the classic arcade game Pac-Man, developed using the C programming language. This project aims to provide an engaging and interactive experience while demonstrating various programming concepts such as game logic, graphics rendering, and user input handling. The game involves navigating Pac-Man through a maze, eating pellets, avoiding ghosts, and trying to achieve the highest score possible.

## Objectives

The main objectives of the Pac-Man project are to:

1. Recreate the gameplay mechanics of the original Pac-Man game.
2. Implement a graphical user interface for rendering the game maze, characters, and other elements.
3. Handle user inputs to control Pac-Man's movements.
4. Develop AI for the ghost characters to chase Pac-Man.
5. Maintain and display the player's score and lives.
6. Ensure smooth and responsive gameplay.

## Features

### Gameplay Mechanics

- **Maze Navigation**: Pac-Man can navigate through a maze filled with pellets.
- **Pellets and Power Pellets**: Eating pellets increases the score, and eating power pellets temporarily allows Pac-Man to eat ghosts.
- **Ghosts**: Four ghosts (Blinky, Pinky, Inky, and Clyde) chase Pac-Man with unique behaviors.
- **Lives**: Pac-Man starts with a set number of lives. A life is lost when a ghost catches Pac-Man.
- **Scoring**: Points are awarded for eating pellets, power pellets, and ghosts.

### Graphical User Interface

- **Rendering**: The game uses a graphical library raylib to render the maze, Pac-Man, ghosts, and other elements.
- **Animations**: Smooth animations for character movements and interactions.
- **HUD**: Display of score, lives, and other game information.

### User Input Handling

- **Keyboard Controls**: Arrow keys or WASD keys to control Pac-Man's direction.
- **Responsive Controls**: Immediate response to user inputs for a smooth gaming experience.

### Ghost AI

- **Chase Mode**: Ghosts actively chase Pac-Man.
- **Scatter Mode**: Ghosts retreat to their corners of the maze.
- **Vulnarable Mode**: When Pac-Man eats 5 power pellets, ghosts become vulnerable and can be eaten.

## Implementation Details

### Development Environment

- **Programming Language**: C
- **Libraries**: Graphics library Raylib for rendering and input handling.
- **IDE**: Any standard C IDE or text editor with GCC for compilation.

### Game Structure

- **Main Loop**: The game runs in a loop that updates game states and renders frames.
- **Game States**: Different states such as playing, paused, game over, etc.
- **Entities**: Separate structures for Pac-Man, ghosts, pellets, and the maze.
- **Collision Detection**: Logic to detect and handle collisions between Pac-Man, ghosts, and maze boundaries.
- **AI Logic**: Implementing different behaviors for ghosts using algorithms.

### Code Organization

- **main.c**: Entry point of the game, containing the main loop ,initialization code and user input  managemnet.
- **pacman.h**:  Drawing Pacman and updating its position.
- **ghost.h**: Ghost AI behaviors and state transitions.
- **logic.h**: Core game logic and collision detection and response logic.
- **GenMaze.h**: Genrating the maze by taking data from a txt file.
- **spath.h**: Used to generate shortest path(Uses A* Algorithm).
- **globe.h**: Contains the globle data structures for the easy acces.
- **ui.h**: Contains all the UI components such as buttons, menu screen, main screen etc.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC).
- Installed graphics library Raylib
- Basic understanding of C programming.

### Installation

1. Clone the repository:
   sh
   git clone https://github.com/Balamurugan1962/PAC-MAN-IN-C/tree/main
   
2. Navigate to the project directory:
   sh
   cd pacman-project
   
3. Compile the project:
   sh
   make
   
4. Run the game:
   sh
   ./pacman
   

### Controls

- Use the arrow keys or WASD keys to control Pac-Man's movement.
- Press 'P' to pause the game.
- Press 'Q' to quit the game.

## Conclusion

The Pac-Man project in C is a fun and educational way to explore game development, understand the complexities of game mechanics, and practice C programming. By working on this project, you will gain insights into game loops, AI programming, graphics rendering, and user input handling. Enjoy the process of bringing this classic game to life!
