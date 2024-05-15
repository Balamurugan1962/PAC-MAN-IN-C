#pragma once

#include "include/raylib.h"
#define HEIGHT 950
#define WIDTH 900
#define MAP_WIDTH 30
#define MAP_HEIGHT 33
#define MAX_LEVEL 1
#define cellsize (WIDTH/30)

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

struct PacmanDetails Pacman = {(Vector2){420,540},(Vector2){0,0},(Vector2){0, 0},(Vector2){0,0},30,0};

struct GHOST{
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    Color color;
    int speed;
    bool isAlive;
};

struct GHOST ghost = {(Vector2){420,420},(Vector2){0,0},(Vector2){0, 0},(Vector2){0,0},RED,30,false};





bool gameOver=false;


//pacman animation
int Level=0;
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