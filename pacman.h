#pragma once

#include "globle.h"

void drawBlock(){
    Rectangle sourceRec = { 0, 0, (float)Pacmantext[currentTextureIndex].width, (float)Pacmantext[currentTextureIndex].height };
    Rectangle destRec = { (float)Pacman.position.x+0.5*cellsize, (float)Pacman.position.y+0.5*cellsize, (float)Pacmantext[currentTextureIndex].width, (float)Pacmantext[currentTextureIndex].height };
    Vector2 origin = { (float)Pacmantext[currentTextureIndex].width / 2, (float)Pacmantext[currentTextureIndex].height / 2 };
        
    DrawTexturePro(Pacmantext[currentTextureIndex], sourceRec, destRec, origin, Pacman.rotation, WHITE);
}




void updateBlock() {
    int tempPosX = Pacman.position.x + Pacman.direction.x;
    int tempPosY = Pacman.position.y + Pacman.direction.y;
    int tempLastPosX = Pacman.position.x + Pacman.LastDirection.x;
    int tempLastPosY = Pacman.position.y + Pacman.LastDirection.y;

    if (boards[Level][tempLastPosY / cellsize][tempLastPosX / cellsize] < 3) {
        Pacman.position.x = tempLastPosX;
        Pacman.position.y = tempLastPosY;
        Pacman.LastValidDirection = Pacman.LastDirection;
        Pacman.direction = Pacman.LastDirection;
    }
   else if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3) {
        Pacman.position.x = tempPosX;
        Pacman.position.y = tempPosY;
        Pacman.LastValidDirection = Pacman.direction;
    }else {
        Pacman.LastDirection=Pacman.direction;
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

    if(Pacman.direction.x>0 && Pacman.direction.y==0) Pacman.rotation=0.0f;
    else if(Pacman.direction.x<0 && Pacman.direction.y==0) Pacman.rotation=180.0f;
    else if(Pacman.direction.x==0 && Pacman.direction.y>0) Pacman.rotation=90.0f;
    else if(Pacman.direction.x==0 && Pacman.direction.y<0) Pacman.rotation=270.0f;
    else Pacman.rotation=0.0f;


}