#pragma once

#include "globle.h"
#include "spath.h"

#define GHOST_MOVE_DELAY 5 // Adjust this value to control the ghost's speed relative to Pac-Man
#define MIN_CHASE_DISTANCE 10 // Minimum distance for ghosts to start chasing Pac-Man

void DrawGhost(){
    if(!isvul)
    for(int i=0;i<4;i++)
    DrawCircle(ghost[i].position.x+0.5*cellsize,ghost[i].position.y+0.5*cellsize,cellsize/2,ghost[i].color);
    else{
        for(int i=0;i<4;i++)
    DrawCircle(ghost[i].position.x+0.5*cellsize,ghost[i].position.y+0.5*cellsize,cellsize/2,GRAY);
    }
}

void updateGhost(int i) {
    int tempPosX = ghost[i].position.x + ghost[i].direction.x;
    int tempPosY = ghost[i].position.y + ghost[i].direction.y;

    // Check if the next position is valid
    if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3 || boards[Level][tempPosY / cellsize][tempPosX / cellsize] == 9) {
        ghost[i].position.x = tempPosX;
        ghost[i].position.y = tempPosY;
        ghost[i].LastValidDirection = ghost[i].direction;
    } else {
        ghost[i].direction = ghost[i].LastValidDirection;
    }

    // Wrap around if reaching screen boundaries
    if (ghost[i].position.x >= WIDTH - cellsize) {
        ghost[i].position.x = 0;
    } else if (ghost[i].position.x < cellsize) {
        ghost[i].position.x = WIDTH - cellsize;
    }

    if (ghost[i].position.y >= HEIGHT - cellsize) {
        ghost[i].position.y = 0;
    } else if (ghost[i].position.y < cellsize) {
        ghost[i].position.y = HEIGHT - cellsize;
    }
}

bool CheckCollisionGhostGhost(Vector2 ghostPos1, Vector2 ghostPos2) {
    float distanceSquared = (ghostPos1.x - ghostPos2.x) * (ghostPos1.x - ghostPos2.x) + (ghostPos1.y - ghostPos2.y) * (ghostPos1.y - ghostPos2.y);
    float radiusSquared = (cellsize / 2) * (cellsize / 2); // Assuming the radius of ghosts is cellsize/2
    return distanceSquared < radiusSquared; // Check if the distance between the ghosts is less than the sum of their radii
}

void updateGhostPosition() {
    for (int i = 0; i < 4; i++) {
        ghostMoveCounter++;
        if (ghostMoveCounter >= GHOST_MOVE_DELAY) {
            ghostMoveCounter = 0; // Reset counter
            
            // Calculate A* path from ghost to Pac-Man's position if the shortest distance is greater than 5
            struct Point ghostpos = {ghost[i].position.x / cellsize, ghost[i].position.y / cellsize};
            struct Point pacmanpos = {ghost[i].Target.x / cellsize, ghost[i].Target.y / cellsize};
            if (BFS(boards, ghostpos, pacmanpos) < 5) {
                struct Point src = {(int)(ghost[i].position.x / cellsize), (int)(ghost[i].position.y / cellsize)};
                struct Point dest = {(int)(ghost[i].Target.x / cellsize), (int)(ghost[i].Target.y / cellsize)};
                struct Point *path = AStar(boards[Level], src, dest, 33, 30);

                // If a valid path exists, move towards Pac-Man
                if (path != NULL) {
                    struct Point nextPos = path[1]; // Next position after the current position
                    ghost[i].direction.x = (nextPos.x - src.x) * cellsize;
                    ghost[i].direction.y = (nextPos.y - src.y) * cellsize;
                    free(path); // Free the allocated memory for the path
                }
            } else if (boards[Level][(int)((ghost[i].position.y + ghost[i].direction.y) / cellsize)][(int)(ghost[i].position.x + ghost[i].direction.x) / cellsize] > 3) {
                // Ghost moves randomly if the shortest distance is less than or equal to 5
                Vector2 possibleDirs[] = {{0, cellsize}, {0, -cellsize}, {cellsize, 0}, {-cellsize, 0}};
                Vector2 randomDir = possibleDirs[GetRandomValue(0, 3)];

                while (randomDir.x == ghost[i].LastValidDirection.x && randomDir.y == ghost[i].LastValidDirection.y)
                    randomDir = possibleDirs[GetRandomValue(0, 3)]; // Get a random direction

                ghost[i].direction = randomDir;
            }

            // Check collision with other ghosts
            for (int j = 0; j < 4; j++) {
                if (i != j) {
                    if (CheckCollisionGhostGhost(ghost[i].position, ghost[j].position)) {
                        // Reverse direction if colliding with another ghost
                        ghost[i].direction.x *= -1;
                        ghost[i].direction.y *= -1;
                        break;
                    }
                }
            }

            // Update ghost's position based on the chosen direction
            updateGhost(i);
        }
    }
}



