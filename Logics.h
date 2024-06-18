#pragma once

#include "globle.h"
#include "MazeGen.h"

int readHighScore() {
    FILE *file = fopen("high_score.csv", "r");
    if (file == NULL) {
        printf("High score file not found. Creating a new one...\n");
        return 0;
    }
    int highScore;
    fscanf(file, "%d", &highScore);
    fclose(file);
    return highScore;
}


void writeHighScore(int score) {
    FILE *file = fopen("high_score.csv", "w");
    if (file == NULL) {
        printf("Error writing high score.\n");
        return;
    }
    fprintf(file, "%d", score);
    fclose(file);
}

bool CheckCollisionPacmanGhost(Vector2 pacmanPos, Vector2 ghostPos) {
    float distance = Vector2Distance(pacmanPos, ghostPos);
    return distance < 30; 
}

void checkcol(){
    int gridX = (int)((Pacman.position.x / cellsize));
    int gridY = (int)((Pacman.position.y / cellsize));

    for(int i=0;i<no_of_ghosts;i++)
    if(ghost[i].isvul){
        if(GetTime()-startTime>=vultime){
        ghost[i].isvul=false;
        startTime=0;}
    }

    if(boards[Level][gridY][gridX]==1){
        boards[Level][gridY][gridX]=0;
        Pacman.score++;
        creditindex=creditindex%2;
        if(shouldaudioplay){
        SetSoundVolume(credit[creditindex],0.1);
        PlaySound(credit[creditindex]);
        }
        creditindex++;
    }

    if(boards[Level][gridY][gridX]==2){
        if(powerplt==5){
            powerplt=0;
            for(int i=0;i<no_of_ghosts;i++)
                ghost[i].isvul=true;
            startTime=GetTime();  
        }
        else{
        Pacman.score+=5;
        powerplt++;
        }
        if(shouldaudioplay){
        SetSoundVolume(pwrplt,0.1);
        PlaySound(pwrplt);
            }
        boards[Level][gridY][gridX]=0;
    }

    for (int i = 0; i < no_of_ghosts; i++) {
        if (CheckCollisionPacmanGhost(Pacman.position, ghost[i].position)&&!ghost[i].dead) {
            if(!ghost[i].isvul){
            Pacman.life--;
            gameOver=true;
            }
            else{
                ghost[i].dead=true;
                if(shouldaudioplay){
                SetSoundVolume(pwrplt,0.1);
                    PlaySound(pwrplt);
                }
                ghost[i].delaytime=0;
                Pacman.score+=100;
            }
        }
    }

}

void levelup(int lvl){

    ClearBackground(BLACK);
    DrawTextEx(font,"PAc - MAN",(Vector2){WIDTH/2-200,50},50,10,YELLOW);
    DrawText(TextFormat("Level %d", lvl),HEIGHT/2-200,(WIDTH/2)-50,100,WHITE);
    DrawText(TextFormat("Score: %d", Pacman.score),HEIGHT/2-100,WIDTH-100,30,WHITE);
    DrawText(TextFormat("Life: %d", Pacman.life),HEIGHT/2-90,WIDTH-50,30,WHITE);
    DrawText("(Press Enter to continue..)",HEIGHT/2-170,WIDTH,20,WHITE);
}

void GameEndScreen(){
    int highScore = readHighScore();
    ClearBackground(BLACK);
    DrawTextEx(font,"PAc - MAN",(Vector2){WIDTH/2-225,50},50,10,YELLOW);
    DrawTextEx(font,"GAME OVER",(Vector2){WIDTH/2-250,HEIGHT/2-50},50,10,WHITE);
    DrawText(TextFormat("Score: %d", Pacman.score),HEIGHT/2-175,WIDTH-50,50,WHITE);
    DrawText(TextFormat("High Score: %d", highScore),HEIGHT/2-190,WIDTH,30,WHITE);
     gameOver=true;
}

void DrawScore() {
    DrawText(TextFormat("Score: %d", Pacman.score),20,HEIGHT, 20, WHITE); 
    DrawText(TextFormat("Life: %d", Pacman.life),WIDTH-120,HEIGHT, 20, WHITE); 
    DrawText(TextFormat("Level: %d", lvl),WIDTH/2-30,HEIGHT, 20, WHITE); 
}

bool noPellet(){
    for(int i=0;i<MAP_HEIGHT;i++)
        for(int j=0;j<MAP_WIDTH;j++)
            if(boards[0][i][j]==1 || boards[0][i][j]==2)
                return false;
    
    return true;
}

void gamelogics(){
    if(Pacman.life<=0) gameOver=true;


        currentTextureIndex = (currentTextureIndex + 1) % 5;
        if(GetTime()-startTime<27)
        ghostspriteindex= (ghostspriteindex + 1)% 2;
        else
        ghostspriteindex= (ghostspriteindex + 1)% 4;
        

        
        
        if(noPellet()){
            lvl++;

            islvlup=true;

            if(islvlup){
            if(no_of_ghosts==1)
                no_of_ghosts=2;
            else if(no_of_ghosts==2)
                no_of_ghosts=4;
            }

            if(lvl%5==0){
                GHOST_MOVE_DELAY=1;
            }else{
                GHOST_MOVE_DELAY=5;
            }
            initvar();
            initmaze();

            lvlstarttime=GetTime();

        }

        if(lvlstarttime%40==0){
            scattertime=fmax(scattertime-5,5);
            chasetime+=5;
        }
}