#include<math.h>
#include "globle.h"
// Define constants
const int MAZE_WIDTH = MAP_WIDTH;
const int MAZE_HEIGHT = 36;
const int NUM_GHOSTS = 4;



// Function to calculate distance between two points
double distance(Vector2 a, Vector2 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

// Function to calculate target tile for Pinky
Vector2 calculatePinkyTargetTile(PacmanDetails& pacman) {
    // Implement Pinky's targeting method
    // Four tiles ahead of Pac-Man's current direction
    Vector2 target;
    switch (pacman.direction.x) {
        case -1:
            target.x = pacman.position.x - 4;
            target.y = pacman.position.y;
            break;
        case 1:
            target.x = pacman.position.x + 4;
            target.y = pacman.position.y;
            break;
        case 0:
            switch (pacman.direction.y) {
                case -1:
                    target.x = pacman.position.x;
                    target.y = pacman.position.y - 4;
                    break;
                case 1:
                    target.x = pacman.position.x;
                    target.y = pacman.position.y + 4;
                    break;
            }
            break;
    }
    return target;
}

// Function to calculate target tile for Inky
Vector2 calculateInkyTargetTile(Pacman& pacman, Ghost& blinky) {
    // Implement Inky's targeting method
    Vector2 target;
    target.x = pacman.position.x + 2 * (pacman.position.x - blinky.position.x);
    target.y = pacman.position.y + 2 * (pacman.position.y - blinky.position.y);
    return target;
}

// Function to calculate target tile for Clyde
Vector2 calculateClydeTargetTile(Pacman& pacman, Ghost& clyde) {
    // Implement Clyde's targeting method
    double dist = distance(pacman.position, clyde.position);
    if (dist > 8) {
        return pacman.position;
    } else {
        return {0, MAZE_HEIGHT}; // Bottom-left corner of maze
    }
}

// Function to update ghost behavior based on current mode
void updateGhostBehavior(Ghost& ghost, int wave, Pacman& pacman, Ghost* ghosts) {
    if (ghost.frightened) {
        // Implement frightened mode behavior
    } else if (wave < 4) {
        // Implement scatter mode behavior
    } else {
        // Implement permanent chase mode behavior
        ghost.targetTile = calculateTargetTile(ghost, pacman, ghosts);
    }
}

// Function to update ghost movement
void updateGhostMovement(Ghost& ghost, Pacman& pacman, Ghost* ghosts) {
    // Implement movement towards target tile
    // Implement collision detection and direction selection
}

// Function to handle ghost exiting ghost house
void handleGhostExitingHouse(Ghost& ghost, int wave) {
    if (wave == 1) {
        // Implement initial behavior for each ghost when exiting ghost house
    }
}

// Main function to update ghost behavior and movement
void updateGhosts(Ghost* ghosts, int wave, Pacman& pacman) {
    for (int i = 0; i < NUM_GHOSTS; ++i) {
        handleGhostExitingHouse(ghosts[i], wave);
        updateGhostBehavior(ghosts[i], wave, pacman, ghosts);
        updateGhostMovement(ghosts[i], pacman, ghosts);
    }
}

int main() {
    // Initialize Pacman
    Pacman pacman;
    pacman.position = {14, 23}; // Example position

    // Initialize Ghosts
    Ghost ghosts[NUM_GHOSTS];
    ghosts[BLINKY].personality = BLINKY;
    ghosts[PINKY].personality = PINKY;
    ghosts[INKY].personality = INKY;
    ghosts[CLYDE].personality = CLYDE;
    // Initialize other properties for each ghost as needed

    // Example wave
    int wave = 1;

    // Update ghost behavior and movement
    updateGhosts(ghosts, wave, pacman);

    return 0;
}
