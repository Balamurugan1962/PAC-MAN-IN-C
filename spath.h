#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globle.h"



struct Point {
    int x;
    int y;
};


struct Node {
    struct Point pos;   
    int gCost;          
    int hCost;          
    int fCost;          
    struct Node *parent;
};


int calculateHeuristic(struct Point start, struct Point end) {
    return abs(end.x - start.x) + abs(end.y - start.y);
}

bool isValidPoint(int maze[][30], int rows, int cols, struct Point point) {
    return point.x >= 0 && point.x < cols && point.y >= 0 && point.y < rows && (maze[point.y][point.x] < 3 || maze[point.y][point.x]==9);
}

bool isGoalPoint(struct Point point, struct Point goal) {
    return point.x == goal.x && point.y == goal.y;
}

int findNodeIndex(struct Node **openList, int openCount, struct Point pos) {
    for (int i = 0; i < openCount; i++) {
        if (openList[i]->pos.x == pos.x && openList[i]->pos.y == pos.y) {
            return i;
        }
    }
    return -1;  // Node not found
}


struct Point* tracePath(struct Node *current) {
    int pathLength = 0;
    struct Node *temp = current;
    while (temp != NULL) {
        pathLength++;
        temp = temp->parent;
    }

    struct Point *path = (struct Point*)malloc(pathLength * sizeof(struct Point));
    temp = current;
    for (int i = pathLength - 1; i >= 0; i--) {
        path[i] = temp->pos;
        temp = temp->parent;
    }

    return path;
}


struct Point* AStar(int maze[][30], struct Point start, struct Point goal, int rows, int cols,int x,int y) {
    int temp=maze[x][y];
    maze[x][y]=3;
    struct Node *openList[rows * cols];
    int openCount = 0;
    bool closedList[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            closedList[i][j] = false;
        }
    }


    struct Node *startNode = (struct Node*)malloc(sizeof(struct Node));
    startNode->pos = start;
    startNode->gCost = 0;
    startNode->hCost = calculateHeuristic(start, goal);
    startNode->fCost = startNode->gCost + startNode->hCost;
    startNode->parent = NULL;
    openList[openCount++] = startNode;

    while (openCount > 0) {
        int currentIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i]->fCost < openList[currentIndex]->fCost) {
                currentIndex = i;
            }
        }

        struct Node *currentNode = openList[currentIndex];

        for (int i = currentIndex; i < openCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openCount--;

        closedList[currentNode->pos.y][currentNode->pos.x] = true;

        if (isGoalPoint(currentNode->pos, goal)) {
            maze[x][y]=temp;
            return tracePath(currentNode);
        }

        struct Point successors[] = {
            {currentNode->pos.x + 1, currentNode->pos.y},
            {currentNode->pos.x - 1, currentNode->pos.y},
            {currentNode->pos.x, currentNode->pos.y + 1},
            {currentNode->pos.x, currentNode->pos.y - 1}
        };

        for (int i = 0; i < 4; i++) {

            if (isValidPoint(maze, rows, cols, successors[i]) && !closedList[successors[i].y][successors[i].x]) {

                int gCost = currentNode->gCost + 1;
                int hCost = calculateHeuristic(successors[i], goal);
                int fCost = gCost + hCost;


                int existingIndex = findNodeIndex(openList, openCount, successors[i]);
                if (existingIndex != -1 && gCost >= openList[existingIndex]->gCost) {
                    continue;
                }


                struct Node *successorNode = (struct Node*)malloc(sizeof(struct Node));
                successorNode->pos = successors[i];
                successorNode->gCost = gCost;
                successorNode->hCost = hCost;
                successorNode->fCost = fCost;
                successorNode->parent = currentNode;


                openList[openCount++] = successorNode;
            }
        }
    }

    maze[x][y]=temp;
    return NULL;
}


#endif /* SHORTESTPATH_H */
