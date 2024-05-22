#pragma once

#include "globle.h"
#include "Levels.h"

#define HEIGHT 950
#define WIDTH 900
#define MAP_WIDTH 30
#define MAP_HEIGHT 33
#define MAX_LEVEL 1
#define cellsize (WIDTH/30)


void DrawMaze(int Level){
    int num1=cellsize;
    int num2=cellsize;
    int center_x, center_y, radius;

    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){

            if(boards[Level][i][j]==1)
            DrawCircle(j*num2+(0.5*num2),i*num1+(0.5*num1),4,WHITE);

            if(boards[Level][i][j]==2)
            DrawCircle(j*num2+(0.5*num2),i*num1+(0.5*num1),10,WHITE);

            if(boards[Level][i][j]==3)
            DrawRectangle(j*num2+(0.5*num2),i*num1+(0.5*num1),3,num1,DARKBLUE);

            if(boards[Level][i][j]==4)
            DrawRectangle(j*num2,i*num1+(0.5*num1),num2,3,DARKBLUE);

            if (boards[Level][i][j] == 5) {
                DrawRectangle(j*num2,i*num1+(0.5*num1),num2/2,3,DARKBLUE);
                DrawRectangle(j*num2+num2/2,i*num1+(0.5*num1),3,num1,DARKBLUE);
            }

            if (boards[Level][i][j] == 6) {
                DrawRectangle(j*num2+num2/2,i*num1+(0.5*num1),num2,3,DARKBLUE);
                DrawRectangle(j*num2+num2/2,i*num1+(0.5*num1),3,num1,DARKBLUE);
            }

            if (boards[Level][i][j] == 7) {
                DrawRectangle(j*num2+num2/2,i*num1+num1/2,num2,3,DARKBLUE);
                DrawRectangle(j*num2+num2/2,i*num1,3,num1/2,DARKBLUE);
            }

            if (boards[Level][i][j] == 8) {
                DrawRectangle(j*num2,i*num1+num1/2,num2/2+3,3,DARKBLUE);
                DrawRectangle(j*num2+num2/2,i*num1,3,num1/2+3,DARKBLUE);
            }
            
            if(boards[Level][i][j]==9) 
            DrawRectangle(j*num2,i*num1+(0.5*num1),num2,3,WHITE);
           /*if(boards[Level][i][j]<3)
            DrawRectangle(j*cellsize+1,i*cellsize+1,cellsize-1,cellsize-1,darkGrey);*/
        }
    }
}
