#pragma once

#include "globle.h"

bool CheckCollisionPacmanGhost(Vector2 pacmanPos, Vector2 ghostPos) {
    float distance = Vector2Distance(pacmanPos, ghostPos);
    return distance < 30; // Assuming the radius of Pacman and ghosts is 15
}

void checkcol(){
     int gridX = (int)((Pacman.position.x / cellsize));
    int gridY = (int)((Pacman.position.y / cellsize));

    if(boards[Level][gridY][gridX]==1){
        boards[Level][gridY][gridX]=0;
        Pacman.score++;
    }

    if(boards[Level][gridY][gridX]==2){
        if(powerplt>=5){
            powerplt=0;
            isvul=true;
        }
        else{
        Pacman.score+=5;
        powerplt++;
        }
        boards[Level][gridY][gridX]=0;
    }

    for (int i = 0; i < 4; i++) {
        if (CheckCollisionPacmanGhost(Pacman.position, ghost[i].position)) {
            if(!isvul)
            gameOver = true;
            else{
                Pacman.score+=100;
                ghost[i].Target=initpos[i];
            }
        }
        else{
            if(ghost[i].Target.x!=initpos[i].x && ghost[i].Target.y!=initpos[i].y )
            ghost[i].Target=Pacman.position;
        }
    }

}

void GameEndScreen(){
    ClearBackground(BLACK);
    DrawText(TextFormat("Game Over %d", Pacman.score),HEIGHT/2,(WIDTH/2),30,WHITE);
     DrawText(TextFormat("Score: %d", Pacman.score),HEIGHT/2,(WIDTH/2)+50,20,WHITE);
     gameOver=true;
}

void DrawScore() {
    DrawText(TextFormat("Score: %d", Pacman.score), 10, 10, 20, WHITE); // Display the score on the screen
}