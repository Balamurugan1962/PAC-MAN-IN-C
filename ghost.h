#pragma once

#include "globle.h"
#include "spath.h"

#define MIN_CHASE_DISTANCE 10


void DrawGhost(){
    for(int i=0;i<no_of_ghosts;i++){
        
    if(ghost[i].direction.x>0 && ghost[i].direction.y==0) ghost[i].eyedirection=4;
    else if(ghost[i].direction.x<0 && ghost[i].direction.y==0) ghost[i].eyedirection=2;
    else if(ghost[i].direction.x==0 && ghost[i].direction.y>0) ghost[i].eyedirection=0;
    else if(ghost[i].direction.x==0 && ghost[i].direction.y<0) ghost[i].eyedirection=6;
        if(!ghost[i].dead && ghost[i].isvul){
            DrawTexture(vul[ghostspriteindex],ghost[i].position.x,ghost[i].position.y,WHITE);
        }
        else if(ghost[i].dead){
            DrawTexture(eyes[ghost[i].eyedirection/2],ghost[i].position.x,ghost[i].position.y,WHITE);
        } 
        else{
            DrawTexture(ghost[i].text[ghost[i].eyedirection+ghostspriteindex%2],ghost[i].position.x,ghost[i].position.y,WHITE);
        }
}
}

void updateGhost(int i) {
    int tempPosX = ghost[i].position.x + ghost[i].direction.x;
    int tempPosY = ghost[i].position.y + ghost[i].direction.y;

    if (boards[Level][tempPosY / cellsize][tempPosX / cellsize] < 3 || boards[Level][tempPosY / cellsize][tempPosX / cellsize] == 9) {
        ghost[i].position.x = tempPosX;
        ghost[i].position.y = tempPosY;
        ghost[i].LastValidDirection = ghost[i].direction;
    } else {
        ghost[i].direction = ghost[i].LastValidDirection;
    }

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
    float radiusSquared = (cellsize / 2) * (cellsize / 2); 
    return distanceSquared < radiusSquared; 
}

void updatetarget(int i){
    if(ghost[i].position.x==initpos[i].x && ghost[i].position.y==initpos[i].y){
        ghost[i].dead=false;
        ghost[i].isvul=false;
        ghost[i].delaytime=GHOST_MOVE_DELAY;
    }

    if(scattermode && !ghost[i].dead)
    if(GetTime()-scatterstarttime<scattertime && no_of_ghosts>1){
        if(isvectorsame(ghost[i].position,Vector2Scale(ghost[i].initTraget[ghost[i].targetindex],cellsize))){
            ghost[i].targetindex=(ghost[i].targetindex+1)%ghost[i].initTragetsize;
            }
        ghost[i].Target=Vector2Scale(ghost[i].initTraget[ghost[i].targetindex],cellsize);
    }
    else{
        scattermode=false;
        chasemode=true;
        chasestarttime=GetTime(); 
    }
    else if(chasemode && !ghost[i].dead){
        if((GetTime()-chasestarttime<chasetime && !ghost[i].isvul) || no_of_ghosts<2){
            ghost[i].Target=Pacman.position;
        }
        else{
            scattermode=true;
            chasemode=false;
            scatterstarttime=GetTime();
        }
        }
    else{
            ghost[i].Target=initpos[i];
        }
}


void updateGhostPosition() {
    
    for (int i = 0; i < no_of_ghosts; i++) {
        ghostMoveCounter++;
        if (ghostMoveCounter >= ghost[i].delaytime) {
            if(!ghost[i].dead)
            ghostMoveCounter = 0; 
            updatetarget(i);

                int tempPosX = (ghost[i].position.x - ghost[i].direction.x)/cellsize;
                int tempPosY = (ghost[i].position.y - ghost[i].direction.y)/cellsize;
                struct Point src = {(int)(ghost[i].position.x / cellsize), (int)(ghost[i].position.y / cellsize)};
                struct Point dest = {(int)(ghost[i].Target.x / cellsize), (int)(ghost[i].Target.y / cellsize)};
                struct Point *path = AStar(boards[Level], src, dest, 33, 30,tempPosY,tempPosX);

                if (path != NULL && !ghost[i].dead) {
                    struct Point nextPos = path[1];
                    ghost[i].direction.x = (nextPos.x - src.x) * cellsize;
                    ghost[i].direction.y = (nextPos.y - src.y) * cellsize;
                    free(path);
                }
                else{
                       path = AStar(boards[Level], src, dest, 33, 30,0,1);
                        struct Point nextPos = path[1];
                        ghost[i].direction.x = (nextPos.x - src.x) * cellsize;
                        ghost[i].direction.y = (nextPos.y - src.y) * cellsize;
                    free(path);
                }

            updateGhost(i);
        }
    }
}
