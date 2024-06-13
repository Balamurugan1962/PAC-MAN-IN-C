#pragma once

#include "include/raylib.h"
#include "include/raymath.h"
#include "spath.h"

#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 990
#define WIDTH 900
#define MAP_WIDTH 30
#define MAP_HEIGHT 33
#define MAX_LEVEL 1
#define cellsize (WIDTH/30)

int boards[MAX_LEVEL][MAP_HEIGHT][MAP_WIDTH];
//int boards[MAP_HEIGHT][MAP_WIDTH];

#define AUDIO_PATH "assets/audio/start.mp3"

enum GhostPersonality { BLINKY, PINKY, INKY, CLYDE };


Texture2D Pacmantext[5];
Texture2D vul[4];
Sound credit[2];
Sound pwrplt;
Music chase;


int num1=(HEIGHT-50)/33;
int num2=WIDTH/30;
Color darkGrey = (Color){26, 31, 40, 255};

struct PacmanDetails{
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    float rotation;
    int speed;
    int score;
    int life;
};



struct GHOST{
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    Vector2 Target;
    Texture2D text[8];
    int eyedirection;
    bool dead;
    Color color;
    int speed;
    GhostPersonality personality;

};


Texture2D eyes[4];
struct PacmanDetails Pacman;
Vector2 initpos[4]={(Vector2){420,450},(Vector2){450,450},(Vector2){450,420},(Vector2){420,420}};

struct GHOST ghost [2];
bool isvul=false;
int powerplt=0;
int ghostMoveCounter = 0; // Counter to control ghost movement



bool gameOver=false;
int Level=0;
int frameCounter = 0;
int currentTextureIndex = 0;
int textureChangeRate = 5;  // Change texture every 20 frames
float startTime=0;
int ghostspriteindex = 0;
int creditindex;
int songstart=0;
int vultime=30;
bool islvlup=false;

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
    Pacman.LastDirection=(Vector2){0, cellsize};
    Pacman.LastValidDirection= (Vector2){0,0};
    Pacman.rotation=0.0f;
    

    ghost[0].position=initpos[0];
    ghost[0].direction=(Vector2){0,0};
    ghost[0].LastDirection=(Vector2){0,0};
    ghost[0].LastValidDirection=(Vector2){0,0};
    ghost[0].color=RED;
    ghost[0].speed=30;
    ghost[0].Target=Pacman.position;
    ghost[0].dead=false;
    ghost[0].eyedirection=0;


    ghost[1].position=initpos[1];
    ghost[1].direction=(Vector2){0,0};
    ghost[1].LastDirection=(Vector2){0,0};
    ghost[1].LastValidDirection=(Vector2){0,0};
    ghost[1].color=GREEN;
    ghost[1].speed=30;
    ghost[1].Target=Pacman.position;
    ghost[1].dead=false;
    ghost[1].eyedirection=0;


    isvul=false;
}

void loadtext(){
    Pacmantext[0] = LoadTexture("assets/sprites/pac/pacClosed.png");
    Pacmantext[1] = LoadTexture("assets/sprites/pac/pacNarrow.png");
    Pacmantext[2] = LoadTexture("assets/sprites/pac/pacNarrow2.png");
    Pacmantext[3] = LoadTexture("assets/sprites/pac/pacWide.png");
    Pacmantext[4] = LoadTexture("assets/sprites/pac/pacWide2.png");

    ghost[0].text[0]= LoadTexture("assets/sprites/ghosts/orange/inkyD1.png");
    ghost[0].text[1]= LoadTexture("assets/sprites/ghosts/orange/inkyD2.png");
    ghost[0].text[2]= LoadTexture("assets/sprites/ghosts/orange/inkyL1.png");
    ghost[0].text[3]= LoadTexture("assets/sprites/ghosts/orange/inkyL2.png");
    ghost[0].text[4]= LoadTexture("assets/sprites/ghosts/orange/inkyR1.png");
    ghost[0].text[5]= LoadTexture("assets/sprites/ghosts/orange/inkyR2.png");
    ghost[0].text[6]= LoadTexture("assets/sprites/ghosts/orange/inkyU1.png");
    ghost[0].text[7]= LoadTexture("assets/sprites/ghosts/orange/inkyU2.png");


    ghost[1].text[0]= LoadTexture("assets/sprites/ghosts/red/blinkyD1.png");
    ghost[1].text[1]= LoadTexture("assets/sprites/ghosts/red/blinkyD2.png");
    ghost[1].text[2]= LoadTexture("assets/sprites/ghosts/red/blinkyL1.png");
    ghost[1].text[3]= LoadTexture("assets/sprites/ghosts/red/blinkyL2.png");
    ghost[1].text[4]= LoadTexture("assets/sprites/ghosts/red/blinkyR1.png");
    ghost[1].text[5]= LoadTexture("assets/sprites/ghosts/red/blinkyR2.png");
    ghost[1].text[6]= LoadTexture("assets/sprites/ghosts/red/blinkyU1.png");
    ghost[1].text[7]= LoadTexture("assets/sprites/ghosts/red/blinkyU2.png");

    eyes[0]= LoadTexture("assets/sprites/ghosts/eyes/downEyes.png");
    eyes[1]= LoadTexture("assets/sprites/ghosts/eyes/leftEyes.png");
    eyes[2]= LoadTexture("assets/sprites/ghosts/eyes/rightEyes.png");
    eyes[3]= LoadTexture("assets/sprites/ghosts/eyes/upEyes.png");

    vul[0]= LoadTexture("assets/sprites/ghosts/vulnerable/blue1.png");
    vul[1]= LoadTexture("assets/sprites/ghosts/vulnerable/blue2.png");
    vul[2]= LoadTexture("assets/sprites/ghosts/vulnerable/white1.png");
    vul[3]= LoadTexture("assets/sprites/ghosts/vulnerable/white2.png");

    credit[0]=LoadSound("assets/audio/munch_1.wav");
    credit[1]=LoadSound("assets/audio/munch_2.wav");
    pwrplt=LoadSound("assets/audio/credit.wav");
    chase=LoadMusicStream("assets/audio/siren_2.mp3");
}
