#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define GHOST 'X'
char templete1[HEIGHT][WIDTH]={
"########################################",
"#                                      #",
"#                #                     #",
"#               # #                    #",
"#              #####                ####",
"              #     #                   ",
"#                                     ##",
"#             #######                  #",
"#             #      #                 #",
"#             #######                  #",
"#             #      #                 #",
"#             #######                  #",
"#                                      #",
"#             #######                  #",
"              #      #                  ",
"#             #######                  #",
"#             #      #                 #",
"#             #######                  #",
"#                                      #",
"########################################"};

 

void initialize(char board[HEIGHT][WIDTH],int templete_number) {
if(templete_number==0){
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(i == 0 || i == HEIGHT-1)
                board[i][j] = WALL;
            else  if(j == 0 || j == WIDTH-1)
                board[i][j] = WALL;
            else
                board[i][j] = EMPTY;
        }
    }
   int count = 50; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (board[i][j] != WALL && board[i][j] != PACMAN) { 
			board[i][j] = WALL; 
			count--; 
		} 
	} 

	int val = 5; 
	while (val--) { 
		int row = (rand() % (HEIGHT + 1)); 
		for (int j = 3; j < WIDTH - 3; j++) { 
			if (board[row][j] != WALL 
				&& board[row][j] != PACMAN) { 
				board[row][j] = WALL; 
			}
			}
			} 
			}
	else{
	  for(int i=0;i<HEIGHT;i++)
	  for(int j=0;j<WIDTH;j++)
	  board[i][j]=templete1[i][j];
	}

}


void display(char board[HEIGHT][WIDTH]) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

