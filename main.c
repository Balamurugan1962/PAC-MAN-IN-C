#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pacman.h"
#include "ghost.h"
#include "globle.h"
#include "Logics.h"
#include "MazeGen.h"
#include "ui.h"

void startScreen(int type)
{

    if(type==1)
    PlaySound(start);
    bool over = false;

    Color buttonColorNormal = BLACK;
    Color buttonColorHover = GRAY;

    Rectangle playButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 100, 200, 50};
    Rectangle menuButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 25, 200, 50};
    Rectangle statsButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 + 50, 200, 50};
    Rectangle exitButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 + 125, 200, 50};


    Button playButton, menuButton, statsButton, exitButton;

    if(type==1)
    initButton(&playButton, playButtonRect, buttonColorNormal, "Play", 20);
    else
    initButton(&playButton, playButtonRect, buttonColorNormal, "Resume", 20);

    initButton(&menuButton, menuButtonRect, buttonColorNormal, "Menu", 20);
    initButton(&statsButton, statsButtonRect, buttonColorNormal, "How to play", 20);
    initButton(&exitButton, exitButtonRect, buttonColorNormal, "Exit", 20);


    while (!over && !WindowShouldClose())
    {
        if (isMouseOverButton(playButton))
            playButton.color = buttonColorHover;
        else
            playButton.color = buttonColorNormal;

        if (isMouseOverButton(menuButton))
            menuButton.color = buttonColorHover;
        else
            menuButton.color = buttonColorNormal;

        if (isMouseOverButton(statsButton))
            statsButton.color = buttonColorHover;
        else
            statsButton.color = buttonColorNormal;

        if (isMouseOverButton(exitButton))
            exitButton.color = buttonColorHover;
        else
            exitButton.color = buttonColorNormal;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (isMouseOverButton(playButton))
            {
                over=true;
            }
            else if (isMouseOverButton(menuButton))
            {
                displayMenu();
            }
            else if (isMouseOverButton(statsButton))
            {
                displayStats();
            }
            else if(isMouseOverButton(exitButton)){
                CloseWindow();
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTextEx(font,"PAc - MAN",(Vector2){WIDTH/2-200,50},50,10,YELLOW);
        drawbutton(menuButton);
        drawbutton(playButton);
        drawbutton(statsButton);
        drawbutton(exitButton);

        EndDrawing();
    }

}



int main() {
    InitWindow(WIDTH, HEIGHT + 50, "PAC MAN");
    SetTargetFPS(10);
    int highScore = readHighScore();
    InitAudioDevice();
    loadtext();
    startScreen(1);
    initmaze();
    initvar();
    Pacman.score=0;
    Pacman.speed=30;
    Pacman.life=3;
    StopSound(start);
    SetSoundVolume(chase,0.1);
    if(shouldaudioplay)
    PlaySound(chase);

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
            Pacman.LastDirection = (Vector2){0, -1 * cellsize};
            }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
            Pacman.LastDirection = (Vector2){0, cellsize};
            }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)){
            Pacman.LastDirection = (Vector2){-1 * cellsize, 0};
            }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
            Pacman.LastDirection = (Vector2){cellsize, 0};
            }
        if(IsKeyPressed(KEY_P)){
            startScreen(0);
        }
        if(IsKeyPressed(KEY_Q)){
            startScreen(1);
            initvar();
            initmaze();
            Pacman.score=0;
            Pacman.speed=30;
            Pacman.life=3;
        }

        if((Pacman.score+1)%5000==0){
            Pacman.life++;
        }

        gamelogics();


        ClearBackground(BLACK);
        
        BeginDrawing();


        if (!gameOver &&  !islvlup) {
            if(!IsSoundPlaying(chase)&&shouldaudioplay){
                PlaySound(chase);
                }
            if(!shouldaudioplay)
                StopSound(chase);
            checkcol();
            DrawMaze(0);
            if(!peacefull){
            DrawGhost();
            updateGhostPosition();
            }
            updateBlock();
            drawBlock();
            DrawScore();



        } else if(islvlup){
            StopSound(chase);
            if(!IsSoundPlaying(start) && shouldaudioplay)
            PlaySound(start);
            levelup(lvl);
            if(IsKeyPressed(KEY_ENTER)){
                islvlup=false;
                StopSound(start);
                scattermode=true;
                scatterstarttime=GetTime();
            }
        } else{
            StopSound(chase);
            GameEndScreen();
            if (Pacman.score > highScore) {
                printf("New high score: %d\n", Pacman.score);
                writeHighScore(Pacman.score);
            }
            if(IsKeyPressed(KEY_ENTER)){
                initvar();
                gameOver=false;


            }
            else if(IsKeyPressed(KEY_ESCAPE)) break;
        }
        EndDrawing();
    }
     for (int i = 0; i < 5; i++) {
        UnloadTexture(Pacmantext[i]);
    }

    for (int i = 0; i < 5; i++) {
        UnloadTexture(Pacmantext[i]);
    }


    CloseWindow();
    
    return 0;
}

