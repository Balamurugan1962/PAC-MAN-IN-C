#include<stdio.h>
#include <stdlib.h> 
#include "Maze.h"

#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define GHOST 'X'

int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
char board[HEIGHT][WIDTH]; 
int food = 0; 
int curr = 0;


int main(){
	initialize(board,1);
	display(board);
	return 0;
}
