#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pacman.h"
#include "ghost.h"
#include "globle.h"
#include "Logics.h"
#include "MazeGen.h"
#include "ui.h"

void startScreen()
{
    bool over = false;

    Color buttonColorNormal = BLACK;
    Color buttonColorHover = GRAY;

    Rectangle playButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 100, 200, 50};
    Rectangle menuButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 25, 200, 50};
    Rectangle statsButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 + 50, 200, 50};
    Rectangle exitButtonRect = {WIDTH / 2 - 100, HEIGHT / 2 + 125, 200, 50};


    Button playButton, menuButton, statsButton, exitButton;
    initButton(&playButton, playButtonRect, buttonColorNormal, "Play", 20);
    initButton(&menuButton, menuButtonRect, buttonColorNormal, "Menu", 20);
    initButton(&statsButton, statsButtonRect, buttonColorNormal, "Stats", 20);
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

        ClearBackground(RAYWHITE);

        drawbutton(menuButton);
        drawbutton(playButton);
        drawbutton(statsButton);
        drawbutton(exitButton);

        EndDrawing();
    }

}

int main() {
    InitWindow(WIDTH, HEIGHT + 50, "PAC MAN");
    SetTargetFPS(60);
    int highScore = readHighScore();
    int lvl=1;
    InitAudioDevice();
    loadtext();
    SetTargetFPS(10);
    initmaze();
    initvar();
    Pacman.score=0;
    Pacman.speed=30;
    Pacman.life=3;
    startScreen();
    PlayMusicStream(chase);
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)){
            Pacman.LastDirection = (Vector2){0, -1 * cellsize};
            }
        if (IsKeyPressed(KEY_DOWN)){
            Pacman.LastDirection = (Vector2){0, cellsize};
            }
        if (IsKeyPressed(KEY_LEFT)){
            Pacman.LastDirection = (Vector2){-1 * cellsize, 0};
            }
        if (IsKeyPressed(KEY_RIGHT)){
            Pacman.LastDirection = (Vector2){cellsize, 0};
            }
        if(IsKeyPressed(KEY_Q)){
            startScreen();
        }

        if(Pacman.life<=0) gameOver=true;


        currentTextureIndex = (currentTextureIndex + 1) % 5;
        if(GetTime()-startTime<27)
        ghostspriteindex= (ghostspriteindex + 1)% 2;
        else
        ghostspriteindex= (ghostspriteindex + 1)% 4;
        


        if(noPellet()){
            lvl++;
            islvlup=true;
            initvar();
            initmaze();
        }



        ClearBackground(BLACK);
        
        BeginDrawing();


        if (!gameOver &&  !islvlup) {
            UpdateMusicStream(chase);
            updateGhostPosition();
            checkcol();
            DrawMaze(0);
            DrawGhost();
            updateBlock();
            drawBlock();
            DrawScore();



        } else if(islvlup){
            levelup(lvl);
            if(IsKeyPressed(KEY_ENTER)){
                islvlup=false;
            }
        } else{
            GameEndScreen();
            if (Pacman.score > highScore) {
                printf("New high score: %d\n", Pacman.score);
                writeHighScore(Pacman.score);
            }
            if(IsKeyPressed(KEY_ENTER)){
                initmaze();
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

