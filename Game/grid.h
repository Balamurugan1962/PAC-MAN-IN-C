#include "vector.h"
#include "stdio.h"
#include "include/raylib.h"

struct Grid{
    int row;
    int col;
    int cellsize;
};

Color darkGrey;
Color green;
Color red;
Color orange;
Color yellow;
Color purple;
Color cyan;
Color blue;

Color color[8];

void InitColors() {
    darkGrey = (Color){26, 31, 40, 255};
    green = (Color){47, 230, 23, 255};
    red = (Color){232, 18, 18, 255};
    orange = (Color){226, 116, 17, 225};
    yellow = (Color){237, 234, 4, 255};
    purple = (Color){166, 0, 247, 255};
    cyan = (Color){21, 204, 209, 255};
    blue = (Color){13, 64, 216, 255};

    color[0] = darkGrey;
    color[1] = green;
    color[2] = red;
    color[3] = orange;
    color[4] = yellow;
    color[5] = purple;
    color[6] = cyan;
    color[7] = blue;
}


struct Grid griddetails={20,10,30};
int grid[20][10];


void InitGrid(){
    for(int i=0;i<griddetails.row;i++)
    for(int j=0;j<griddetails.col;j++)
        grid[i][j]=0;    
}

void printGrid(){
    for(int i=0;i<griddetails.row;i++){
    for(int j=0;j<griddetails.col;j++)
        printf("%d",grid[i][j]);
        printf("\n");
    }
}

void drawGrid(){
    for(int row=0;row<griddetails.row;row++)
    for(int col=0;col<griddetails.col;col++){
        int celval=grid[row][col];
        DrawRectangle(col*griddetails.cellsize+1,row*griddetails.cellsize+1,griddetails.cellsize-1,griddetails.cellsize-1,color[celval] );
    }
}

