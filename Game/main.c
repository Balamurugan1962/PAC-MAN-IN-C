#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pacman.h"
#include "ghost.h"
#include "Logics.h"
#include "globle.h"
//Color darkblue = {44,44,127,255};



int main() {
    InitWindow(WIDTH, HEIGHT + 50, "PAC MAN");
    SetTargetFPS(9);
    initvar();


    while (!WindowShouldClose()) {
         if (IsKeyPressed(KEY_UP))
            Pacman.direction = (Vector2){0, -1 * cellsize};
        if (IsKeyPressed(KEY_DOWN))
            Pacman.direction = (Vector2){0, cellsize};
        if (IsKeyPressed(KEY_LEFT))
            Pacman.direction = (Vector2){-1 * cellsize, 0};
        if (IsKeyPressed(KEY_RIGHT))
            Pacman.direction = (Vector2){cellsize, 0};
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D))
            Pacman.LastDirection = Pacman.direction;

        if (Pacman.score >= 262)
            gameOver = true;

        ClearBackground(BLACK);
        BeginDrawing();
        if (!gameOver) {
            updateGhostPosition();
            checkcol();
            DrawMaze(0);
            DrawGhost();
            updateBlock();
            drawBlock();
            DrawScore();
        } else {
            GameEndScreen();
            if (IsKeyPressed(KEY_ENTER)) {
                break;
            }
        }
        EndDrawing();
;
    }

    CloseWindow();
    return 0;
}
