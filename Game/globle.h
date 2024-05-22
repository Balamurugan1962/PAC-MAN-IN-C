#pragma once

#include "include/raylib.h"
#include "MazeGen.h"
#include "Levels.h"
#include "include/raymath.h"


int num1=(HEIGHT-50)/33;
int num2=WIDTH/30;
Color darkGrey = (Color){26, 31, 40, 255};

struct PacmanDetails{
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    int speed;
    int score;
};



struct GHOST{
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    Vector2 Target;
    Color color;
    int speed;

};


struct PacmanDetails Pacman;
Vector2 initpos[4]={(Vector2){420,420},(Vector2){420,450},(Vector2){450,420},(Vector2){450,450}};

struct GHOST ghost [4];
bool isvul=false;
int powerplt=0;
int ghostMoveCounter = 0; // Counter to control ghost movement



bool gameOver=false;
int Level=0;

/*
//pacman animation

bool drawPac = true;
int animCounter = 0;
const int animMax = 4;
bool drawWide = true;
bool drawNarrow = false;
bool drawClosed = false;
bool drawNarrow2 = false;

//pacman death animation
int deathFrameCounter = 0;
const int deathAnimMax = 8;
bool dead = false;
*/

void initvar(){
    Pacman.direction = (Vector2){0,0};
    Pacman.position= (Vector2){420,540};
    Pacman.LastDirection=(Vector2){0, 0};
    Pacman.LastValidDirection= (Vector2){0,0};
    Pacman.score=0;
    Pacman.speed=30;

    ghost[0].position=(Vector2){420,420};
    ghost[0].direction=(Vector2){0,0};
    ghost[0].LastDirection=(Vector2){0,0};
    ghost[0].LastValidDirection=(Vector2){0,0};
    ghost[0].color=RED;
    ghost[0].speed=30;
    ghost[0].Target=Pacman.position;

    ghost[1].position=(Vector2){420,450};
    ghost[1].direction=(Vector2){0,0};
    ghost[1].LastDirection=(Vector2){0,0};
    ghost[1].LastValidDirection=(Vector2){0,0};
    ghost[1].color=GREEN;
    ghost[1].speed=30;
    ghost[1].Target=Pacman.position;

    ghost[2].position=(Vector2){450,420};
    ghost[2].direction=(Vector2){0,0};
    ghost[2].LastDirection=(Vector2){0,0};
    ghost[2].LastValidDirection=(Vector2){0,0};
    ghost[2].color=BLUE;
    ghost[2].speed=30;
    ghost[2].Target=Pacman.position;

    ghost[3].position=(Vector2){450,450};
    ghost[3].direction=(Vector2){0,0};
    ghost[3].LastDirection=(Vector2){0,0};
    ghost[3].LastValidDirection=(Vector2){0,0};
    ghost[3].color=PINK;
    ghost[3].speed=30;
    ghost[3].Target=Pacman.position;
}