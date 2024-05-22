#pragma once

#include "globle.h"


void drawBlock(){
    DrawCircle(Pacman.position.x+0.5*cellsize,Pacman.position.y+0.5*cellsize,cellsize/2,YELLOW);
}




void updateBlock() {
    int tempPosX = Pacman.position.x + Pacman.direction.x;
    int tempPosY = Pacman.position.y + Pacman.direction.y;

    if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3 || boards[Level][tempPosY / cellsize][tempPosX / cellsize]==9) {
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