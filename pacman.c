#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '.'
#define EMPTY ' '
#define DEMON 'X'

int res = 0;
int score = 0;
int pacman_x, pacman_y;
char board[HEIGHT][WIDTH];
int food = 0;
int curr = 0;

typedef struct {
    int x, y;
} Demon;

Demon demons[10];

void initialize() {
    srand(time(NULL));

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1) {
                board[i][j] = WALL;
            } else {
                board[i][j] = EMPTY;
            }
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
            if (board[row][j] != WALL && board[row][j] != PACMAN) {
                board[row][j] = WALL;
            }
        }
    }

    count = 10;
    while (count != 0) {
        int i = (rand() % (HEIGHT + 1));
        int j = (rand() % (WIDTH + 1));

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = DEMON;
            demons[count-1].x = j;
            demons[count-1].y = i;
            count--;
        }
    }

    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_y][pacman_x] = PACMAN;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] != WALL && board[i][j] != DEMON && board[i][j] != PACMAN) {
                board[i][j] = FOOD;
                food++;
            }
        }
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void move(int move_x, int move_y) {
    int x = pacman_x + move_x;
    int y = pacman_y + move_y;

    if (board[y][x] != WALL) {
        if (board[y][x] == FOOD) {
            score++;
            food--;
            curr++;
            if (food == 0) {
                res = 2;
                return;
            }
        } else if (board[y][x] == DEMON) {
            res = 1;
        }

        board[pacman_y][pacman_x] = EMPTY;
        pacman_x = x;
        pacman_y = y;
        board[pacman_y][pacman_x] = PACMAN;
    }
}

void moveDemons() {
    for (int i = 0; i < 10; i++) {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;

        if (demons[i].x + dx >= 0 && demons[i].x + dx < WIDTH &&
            demons[i].y + dy >= 0 && demons[i].y + dy < HEIGHT &&
            board[demons[i].y + dy][demons[i].x + dx] != WALL) {
            board[demons[i].y][demons[i].x] = EMPTY;
            demons[i].x += dx;
            demons[i].y += dy;
            board[demons[i].y][demons[i].x] = DEMON;
        }
    }
}

int main() {
    initialize();
    char c;
    food -= 35;
    int totalFood = food;

    printf(" Use buttons for w(up), a(left) , d(right) and "
        "s(down)\nAlso, Press q for quit\n");
    printf("Enter Y to continue: \n");

    c = getchar();
    if (c != 'Y' && c != 'y') {
        printf("Exit Game! ");
        return 1;
    }

    while (1) {
        draw();
        printf("Total Food count: %d\n", totalFood);
        printf("Total Food eaten: %d\n", curr);
        if (res == 1) {
            system("cls");
            printf("Game Over! Dead by Demon\n Your Score: %d\n", score);
            return 1;
        }

        if (res == 2) {
            system("cls");
            printf("You Win! \n Your Score: %d\n", score);
            return 1;
        }

        c = getchar();

        switch (c) {
        case 'w':
            move(0, -1);
            break;
        case 's':
            move(0, 1);
            break;
        case 'a':
            move(-1, 0);
            break;
        case 'd':
            move(1, 0);
            break;
        case 'q':
            printf("Game Over! Your Score: %d\n", score);
            return 0;
        }

        moveDemons(); // Move demons after each player move
    }

    return 0;
}
