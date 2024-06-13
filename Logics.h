#pragma once

#include "globle.h"


void* playAudio(void* arg) {
    InitAudioDevice();

    Sound sound = LoadSound(AUDIO_PATH);
    if (IsSoundReady(sound)) {
        PlaySound(sound);
    } else {
        fprintf(stderr, "Unable to load audio: %s\n", AUDIO_PATH);
    }

    while (IsSoundPlaying(sound)) {} // Wait for audio to finish playing

    UnloadSound(sound);
    CloseAudioDevice();
    
    return NULL;
}

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
    return distance < 45; // Assuming the radius of Pacman and ghosts is 15
}

void checkcol(){
    int gridX = (int)((Pacman.position.x / cellsize));
    int gridY = (int)((Pacman.position.y / cellsize));

    if(isvul){
        if(GetTime()-startTime>=vultime){
        isvul=false;
        startTime=0;}
    }

    if(boards[Level][gridY][gridX]==1){
        boards[Level][gridY][gridX]=0;
        Pacman.score++;
        creditindex=creditindex%2;
        PlaySound(credit[creditindex]);
        creditindex++;
    }

    if(boards[Level][gridY][gridX]==2){
        if(powerplt==5){
            powerplt=0;
            isvul=true;
            startTime=GetTime();
        }
        else{
        Pacman.score+=5;
        powerplt++;
        }
        boards[Level][gridY][gridX]=0;
    }

    for (int i = 0; i < 2; i++) {
        if (CheckCollisionPacmanGhost(Pacman.position, ghost[i].position)&&!ghost[i].dead) {
            if(!isvul){
            Pacman.life--;
            gameOver=true;
            }
            else{
                ghost[i].dead=true;
                Pacman.score+=100;
            }
        }
    }

}

void levelup(int lvl){

    ClearBackground(BLACK);
    DrawText(TextFormat("Level %d", lvl),HEIGHT/2-100,(WIDTH/2),50,WHITE);
    DrawText(TextFormat("Score: %d", Pacman.score),HEIGHT/2-50,(WIDTH/2)+50,30,WHITE);
    DrawText(TextFormat("Life: %d", Pacman.life),HEIGHT/2-50,(WIDTH/2)+100,30,WHITE);
   // playAudio();
    
}

void GameEndScreen(){
    ClearBackground(BLACK);
    DrawText(TextFormat("Game Over %d", Pacman.score),HEIGHT/2,(WIDTH/2),30,WHITE);
     DrawText(TextFormat("Score: %d", Pacman.score),HEIGHT/2,(WIDTH/2)+50,20,WHITE);
     gameOver=true;
}

void DrawScore() {
    DrawText(TextFormat("Score: %d", Pacman.score),20,HEIGHT, 20, WHITE); 
    DrawText(TextFormat("Life: %d", Pacman.life),WIDTH-120,HEIGHT, 20, WHITE); 

}

void ss(){
    int highScore = readHighScore();
    pthread_t audioThread;
    pthread_create(&audioThread, NULL, playAudio, NULL); // Create a thread to play audio


    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose()) {
        ClearBackground(BLACK);
        DrawText("Welcome to PAC MAN!",WIDTH/2-(cellsize*3),HEIGHT/2-(cellsize*3),20, WHITE);
        DrawText("Use arrow keys to move Pac-Man.", WIDTH/2-(cellsize*5),HEIGHT/2-(cellsize),20, WHITE);
        DrawText("Avoid ghosts and eat all the pellets.", WIDTH/2-(cellsize*5),HEIGHT/2+(cellsize), 20, WHITE);
        DrawText("Press ENTER to start the game.", WIDTH/2-(cellsize*5),HEIGHT/2+(cellsize*3), 20, WHITE);
        DrawText(TextFormat("High score: %d", highScore), WIDTH/2-(cellsize*3),HEIGHT/2+(cellsize*5), 20, WHITE);
        EndDrawing();
    }
    pthread_join(audioThread, NULL);
}

bool noPellet(){
    for(int i=0;i<MAP_HEIGHT;i++)
        for(int j=0;j<MAP_WIDTH;j++)
            if(boards[0][i][j]==1 || boards[0][i][j]==2)
                return false;
    
    return true;
}