#pragma once

#include "include/raylib.h"
#include "include/raymath.h"
#include "spath.h"

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


Texture2D Pacmantext[5];
Texture2D vul[4];
Sound credit[2];
Sound pwrplt;
Sound chase;
Font font;
Sound start;

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



typedef struct {
    Vector2 position;
    Vector2 direction;
    Vector2 LastDirection;
    Vector2 LastValidDirection;
    Vector2 Target;
    Texture2D text[8];
    int eyedirection;
    bool dead;
    bool isvul;
    Color color;
    int speed;
    int delaytime;
    Vector2 initTraget[24];
    int targetindex;
    int initTragetsize;
} GHOST;


Texture2D eyes[4];
struct PacmanDetails Pacman;
Vector2 initpos[4]={(Vector2){420,450},(Vector2){450,450},(Vector2){450,420},(Vector2){420,420}};


GHOST ghost [4];
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
int vultime=20;
bool islvlup=false;
int GHOST_MOVE_DELAY;
int no_of_ghosts=2;
int GHOST_MOVE_DELAY =  3; 
int scatterstarttime;
bool scattermode=true;
bool chasemode=false;
int scattertime=10;
int chasetime=10;
int chasestarttime=0;
int lvlstarttime=0;
int lvl=1;
bool shouldaudioplay=true;
bool peacefull=false;
//pacman death animation
int deathFrameCounter = 0;
const int deathAnimMax = 8;
bool dead = false;



bool isvectorsame(Vector2 vec1,Vector2 vec2){
    return(vec1.x==vec2.x && vec1.y==vec2.y);
}

void init4ghost(){
    ghost[0].initTraget[0]=(Vector2){2,21};
    ghost[0].initTraget[1]=(Vector2){2,24};
    ghost[0].initTraget[2]=(Vector2){4,24};
    ghost[0].initTraget[3]=(Vector2){4,27};
    ghost[0].initTraget[4]=(Vector2){2,27};
    ghost[0].initTraget[5]=(Vector2){2,30};
    ghost[0].initTraget[6]=(Vector2){13,30};
    ghost[0].initTraget[7]=(Vector2){13,27};
    ghost[0].initTraget[8]=(Vector2){10,27};
    ghost[0].initTraget[9]=(Vector2){10,24};
    ghost[0].initTraget[10]=(Vector2){13,24};
    ghost[0].initTraget[11]=(Vector2){13,21};
    ghost[0].targetindex=0;
    ghost[0].initTragetsize=12;
    ghost[0].delaytime=GHOST_MOVE_DELAY;


    ghost[1].initTraget[0]=(Vector2){27,21};
    ghost[1].initTraget[1]=(Vector2){27,24};
    ghost[1].initTraget[2]=(Vector2){25,24};
    ghost[1].initTraget[3]=(Vector2){25,27};
    ghost[1].initTraget[4]=(Vector2){27,27};
    ghost[1].initTraget[5]=(Vector2){27,30};
    ghost[1].initTraget[6]=(Vector2){16,30};
    ghost[1].initTraget[7]=(Vector2){16,27};
    ghost[1].initTraget[8]=(Vector2){19,27};
    ghost[1].initTraget[9]=(Vector2){19,24};
    ghost[1].initTraget[10]=(Vector2){16,24};
    ghost[1].initTraget[11]=(Vector2){16,21};
    ghost[1].targetindex=0;
    ghost[1].initTragetsize=12;
    ghost[1].delaytime=GHOST_MOVE_DELAY;


    ghost[2].initTraget[0]=(Vector2){2,2};
    ghost[2].initTraget[1]=(Vector2){13,2};
    ghost[2].initTraget[2]=(Vector2){13,6};
    ghost[2].initTraget[3]=(Vector2){7,6};
    ghost[2].initTraget[4]=(Vector2){7,9};
    ghost[2].initTraget[5]=(Vector2){2,9};
    ghost[2].targetindex=0;
    ghost[2].initTragetsize=6;
    ghost[2].delaytime=GHOST_MOVE_DELAY;


    ghost[3].initTraget[0]=(Vector2){16,2};
    ghost[3].initTraget[1]=(Vector2){27,2};
    ghost[3].initTraget[2]=(Vector2){27,9};
    ghost[3].initTraget[3]=(Vector2){22,9};
    ghost[3].initTraget[4]=(Vector2){22,6};
    ghost[3].initTraget[5]=(Vector2){16,6};
    ghost[3].targetindex=0;
    ghost[3].initTragetsize=6;
    ghost[3].delaytime=GHOST_MOVE_DELAY;

}

void init2ghost(){
    ghost[0].initTraget[0]=(Vector2){16,2};
    ghost[0].initTraget[1]=(Vector2){27,2};
    ghost[0].initTraget[2]=(Vector2){27,9};
    ghost[0].initTraget[3]=(Vector2){22,9};
    ghost[0].initTraget[4]=(Vector2){22,6};
    ghost[0].initTraget[5]=(Vector2){7,6};
    ghost[0].initTraget[6]=(Vector2){7,9};
    ghost[0].initTraget[7]=(Vector2){2,9};
    ghost[0].initTraget[8]=(Vector2){2,2};
    ghost[0].initTraget[9]=(Vector2){13,2};
    ghost[0].initTraget[10]=(Vector2){13,6};
    ghost[0].initTraget[11]=(Vector2){16,6};
    ghost[0].targetindex=0;
    ghost[0].initTragetsize=12;
    ghost[0].delaytime=GHOST_MOVE_DELAY;


    ghost[1].initTraget[0]=(Vector2){27,21};
    ghost[1].initTraget[1]=(Vector2){27,24};
    ghost[1].initTraget[2]=(Vector2){25,24};
    ghost[1].initTraget[3]=(Vector2){25,27};
    ghost[1].initTraget[4]=(Vector2){27,27};
    ghost[1].initTraget[5]=(Vector2){27,30};
    ghost[1].initTraget[6]=(Vector2){2,30};
    ghost[1].initTraget[7]=(Vector2){2,27};
    ghost[1].initTraget[8]=(Vector2){2,27};
    ghost[1].initTraget[9]=(Vector2){4,24};
    ghost[1].initTraget[10]=(Vector2){2,24};
    ghost[1].initTraget[11]=(Vector2){2,21};
    ghost[1].initTraget[12]=(Vector2){13,21};
    ghost[1].initTraget[13]=(Vector2){13,24};
    ghost[1].initTraget[14]=(Vector2){13,24};
    ghost[1].initTraget[15]=(Vector2){13,24};
    ghost[1].targetindex=0;
    ghost[1].initTragetsize=16;
    ghost[1].delaytime=GHOST_MOVE_DELAY;

}

void init1ghost(){
    scattertime=0;
        scattermode=false;
        chasemode=true;
        no_of_ghosts=1;
        ghost[0].initTraget[0]=Pacman.position;
        ghost[0].targetindex=0;
        ghost[0].initTragetsize=1;
        ghost[0].delaytime=GHOST_MOVE_DELAY;
        GHOST_MOVE_DELAY=3;
}
void initvar(){
    
    Pacman.direction = (Vector2){0,0};
    Pacman.position= (Vector2){420,540};
    Pacman.LastDirection=(Vector2){0, cellsize};
    Pacman.LastValidDirection= (Vector2){0,0};
    Pacman.rotation=0.0f;
    scattermode=true;
    chasemode=false;
    

    ghost[0].position=initpos[0];
    ghost[0].direction=(Vector2){0,0};
    ghost[0].LastDirection=(Vector2){0,0};
    ghost[0].LastValidDirection=(Vector2){0,0};
    ghost[0].color=RED;
    ghost[0].speed=30;
    ghost[0].Target=Pacman.position;
    ghost[0].dead=false;
    ghost[0].eyedirection=0;
    ghost[0].isvul=false;
    

    ghost[1].position=initpos[1];
    ghost[1].direction=(Vector2){0,0};
    ghost[1].LastDirection=(Vector2){0,0};
    ghost[1].LastValidDirection=(Vector2){0,0};
    ghost[1].color=GREEN;
    ghost[1].speed=30;
    ghost[1].Target=Pacman.position;
    ghost[1].dead=false;
    ghost[1].eyedirection=0;
    ghost[1].isvul=false;
   


    ghost[2].position=initpos[2];
    ghost[2].direction=(Vector2){0,0};
    ghost[2].LastDirection=(Vector2){0,0};
    ghost[2].LastValidDirection=(Vector2){0,0};
    ghost[2].color=GREEN;
    ghost[2].speed=30;
    ghost[2].Target=Pacman.position;
    ghost[2].dead=false;
    ghost[2].eyedirection=0;
    ghost[2].isvul=false;
    

    ghost[3].position=initpos[3];
    ghost[3].direction=(Vector2){0,0};
    ghost[3].LastDirection=(Vector2){0,0};
    ghost[3].LastValidDirection=(Vector2){0,0};
    ghost[3].color=GREEN;
    ghost[3].speed=30;
    ghost[3].Target=Pacman.position;
    ghost[3].dead=false;
    ghost[3].eyedirection=0;
    ghost[3].isvul=false;
    
    if(no_of_ghosts==4)
    init4ghost();
    else if(no_of_ghosts==2)
    init2ghost();
    else
    init1ghost();

    scatterstarttime=GetTime();

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

    ghost[2].text[0]= LoadTexture("assets/sprites/ghosts/pink/pinkyD1.png");
    ghost[2].text[1]= LoadTexture("assets/sprites/ghosts/pink/pinkyD2.png");
    ghost[2].text[2]= LoadTexture("assets/sprites/ghosts/pink/pinkyL1.png");
    ghost[2].text[3]= LoadTexture("assets/sprites/ghosts/pink/pinkyL2.png");
    ghost[2].text[4]= LoadTexture("assets/sprites/ghosts/pink/pinkyR1.png");
    ghost[2].text[5]= LoadTexture("assets/sprites/ghosts/pink/pinkyR2.png");
    ghost[2].text[6]= LoadTexture("assets/sprites/ghosts/pink/pinkyU1.png");
    ghost[2].text[7]= LoadTexture("assets/sprites/ghosts/pink/pinkyU2.png");

    ghost[3].text[0]= LoadTexture("assets/sprites/ghosts/blue/clydeD1.png");
    ghost[3].text[1]= LoadTexture("assets/sprites/ghosts/blue/clydeD2.png");
    ghost[3].text[2]= LoadTexture("assets/sprites/ghosts/blue/clydeL1.png");
    ghost[3].text[3]= LoadTexture("assets/sprites/ghosts/blue/clydeL2.png");
    ghost[3].text[4]= LoadTexture("assets/sprites/ghosts/blue/clydeR1.png");
    ghost[3].text[5]= LoadTexture("assets/sprites/ghosts/blue/clydeR2.png");
    ghost[3].text[6]= LoadTexture("assets/sprites/ghosts/blue/clydeU1.png");
    ghost[3].text[7]= LoadTexture("assets/sprites/ghosts/blue/clydeU2.png");
    

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
    chase=LoadSound("assets/audio/siren_1.wav");
    font = LoadFont("assets/fonts/PAC-FONT.TTF");
    start=LoadSound("assets/audio/start.mp3");
}
