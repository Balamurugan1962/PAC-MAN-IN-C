#include <stdio.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "MazeGen.h"
#include "globle.h"
#include "spath.h"


Color darkblue = {44,44,127,255};

Vector2 getNextStepDirection(struct Point currentPos, struct Point targetPos) {
    // Calculate the relative position of the target compared to the current position
    int deltaX = targetPos.x - currentPos.x;
    int deltaY = targetPos.y - currentPos.y;

    // Determine the direction of the next step based on the relative position
    Vector2 nextStepDirection = {0, 0};

    if (deltaX > 0) {
        nextStepDirection.x = 1; // Move right
    } else if (deltaX < 0) {
        nextStepDirection.x = -1; // Move left
    } else if (deltaY > 0) {
        nextStepDirection.y = 1; // Move down
    } else if (deltaY < 0) {
        nextStepDirection.y = -1; // Move up
    }

    return nextStepDirection;
}

void DrawGhost(){
    DrawRectangle(ghost.position.x+1,ghost.position.y+1,cellsize-1,cellsize-1,ghost.color);
}

void GetDirection(Vector2 targetPosition) {

    if(!ghost.isAlive){
        if(boards[Level][(int)ghost.position.x/cellsize][(int)ghost.position.y/cellsize]==-1 || boards[Level][(int)ghost.position.x/cellsize][(int)ghost.position.y/cellsize]==9)
            ghost.direction=(Vector2){0,-1*cellsize};
        else
            ghost.isAlive=true;
    }
    else{
    // Calculate the shortest path from ghost's position to the target position (Pacman)
    struct Point ghostPos = {(int)(ghost.position.x / cellsize), (int)(ghost.position.y / cellsize)};
    struct Point targetPos = {(int)(targetPosition.x / cellsize), (int)(targetPosition.y / cellsize)};
    int shortestPathDist = BFS(boards, ghostPos, targetPos);
    printf("%d\n",shortestPathDist);
    // If a valid shortest path exists, move the ghost towards Pacman
    if (shortestPathDist != -1) {
        // Get the direction of the next step in the shortest path
        // You need to implement this function based on your game's logic

        ghost.direction = getNextStepDirection(ghostPos, targetPos);
    }
    }
}

void updateGhostPosition(){
    GetDirection(Pacman.position);
    int tempPosX = Pacman.position.x + Pacman.direction.x;
    int tempPosY = Pacman.position.y + Pacman.direction.y;

    if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3) {
        Pacman.position.x = tempPosX;
        Pacman.position.y = tempPosY;
        Pacman.LastValidDirection = Pacman.direction;
    } else {
        Pacman.direction = Pacman.LastValidDirection;
    }

    if (Pacman.position.x >= WIDTH - cellsize) {
        Pacman.position.x = 0;
    } else if (Pacman.position.x < cellsize) {
        Pacman.position.x = WIDTH - cellsize;
    }

    if (Pacman.position.y >= HEIGHT - cellsize) {
        Pacman.position.y = 0;
    } else if (Pacman.position.y < cellsize) {
        Pacman.position.y = HEIGHT - cellsize;
    }

}
    
    


void drawBlock(){
    DrawRectangle(Pacman.position.x+1,Pacman.position.y+1,cellsize-1,cellsize-1,YELLOW);
}


void updateBlock() {
    int tempPosX = ghost.position.x + ghost.direction.x;
    int tempPosY = ghost.position.y + ghost.direction.y;

    if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3 || boards[Level][tempPosY / cellsize][tempPosX / cellsize]==9) {
        ghost.position.x = tempPosX;
        ghost.position.y = tempPosY;
        ghost.LastValidDirection = ghost.direction;
    } else {
        ghost.direction = ghost.LastValidDirection;
    }

    if (ghost.position.x >= WIDTH - cellsize) {
        ghost.position.x = 0;
    } else if (ghost.position.x < cellsize) {
        ghost.position.x = WIDTH - cellsize;
    }

    if (ghost.position.y >= HEIGHT - cellsize) {
        ghost.position.y = 0;
    } else if (ghost.position.y < cellsize) {
        ghost.position.y = HEIGHT - cellsize;
    }
}

void checkcol(){
     int gridX = (int)((Pacman.position.x / cellsize));
    int gridY = (int)((Pacman.position.y / cellsize));

    if(boards[Level][gridY][gridX]==1){
        boards[Level][gridY][gridX]=0;
        Pacman.score++;
    }

    if(boards[Level][gridY][gridX]==2){
        boards[Level][gridY][gridX]=0;
        Pacman.score+=5;
    }

}

int main(){
    InitWindow(WIDTH,HEIGHT+50,"New Game");
    SetTargetFPS(5);

    while (!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_W))     Pacman.direction=(Vector2){0,-1*cellsize};
        if(IsKeyPressed(KEY_S))    Pacman.direction=(Vector2){0,cellsize};
        if(IsKeyPressed(KEY_A))    Pacman.direction=(Vector2){-1*cellsize,0};
        if(IsKeyPressed(KEY_D))    Pacman.direction=(Vector2){cellsize,0};
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) Pacman.LastDirection=Pacman.direction;

        updateGhostPosition();

        BeginDrawing();
        ClearBackground(BLACK);
        checkcol();
        DrawMaze(0);
        DrawGhost();
        updateBlock();
        drawBlock();
        EndDrawing();
    }
    
}