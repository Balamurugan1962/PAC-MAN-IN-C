#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globle.h"
#include "Levels.h"


// To store matrix cell coordinates
struct Point {
    int x;
    int y;
};

// A Data Structure for queue used in BFS
struct queueNode {
    struct Point pt; // The coordinates of a cell
    int dist; // Cell's distance from the source
};

// Array to store row and column numbers of 4 neighbors of a given cell
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

// Check whether given cell (row, col) is a valid cell or not
static inline bool isValid(int row, int col) {
    // Return true if row number and column number are in range and matrix[i][j] is not a wall (value 3)
    return (row >= 0) && (row < MAP_HEIGHT) && (col >= 0) && (col < MAP_WIDTH) &&
           (boards[Level][row][col] <3 || boards[Level][row][col] == 9);
}

// Function to find the shortest path between a given source cell to a destination cell
static inline int BFS(int mat[][MAP_HEIGHT][MAP_WIDTH], struct Point src, struct Point dest) {
    // Check if source and destination cells of the matrix are not walls (value 3)
    if (mat[Level][src.x][src.y] == 3 || mat[Level][dest.x][dest.y] == 3)
        return -1;

    bool visited[MAP_HEIGHT][MAP_WIDTH];
    memset(visited, false, sizeof(visited));

    // Mark the source cell as visited
    visited[src.x][src.y] = true;

    // Create a queue for BFS
    struct queueNode* q = (struct queueNode*)malloc(MAP_HEIGHT * MAP_WIDTH * sizeof(struct queueNode));
    int front = 0, rear = 0;

    // Initialize queue with source cell
    q[rear].pt = src;
    q[rear].dist = 0;
    rear++;

    // Do a BFS starting from source cell
    while (front < rear) {
        struct Point pt = q[front++].pt;

        // If we have reached the destination cell, we are done
        if (pt.x == dest.x && pt.y == dest.y)
            return q[front - 1].dist;

        // Otherwise, enqueue the adjacent cells
        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // If adjacent cell is valid and not visited yet, mark it as visited and enqueue it
            if (isValid(row, col) && !visited[row][col]) {
                visited[row][col] = true;
                struct queueNode Adjcell = { {row, col}, q[front - 1].dist + 1 };
                q[rear++] = Adjcell;
            }
        }
    }

    // Return -1 if destination cannot be reached
    return -1;
}

// Define a struct for a node in the A* search
struct Node {
    struct Point pos;   // Position of the node in the maze
    int gCost;          // Cost from the start node to this node
    int hCost;          // Heuristic cost from this node to the goal node
    int fCost;          // Total cost (gCost + hCost)
    struct Node *parent;// Parent node (used for reconstructing the path)
};

// Function to calculate the Manhattan distance heuristic between two points
int calculateHeuristic(struct Point start, struct Point end) {
    return abs(end.x - start.x) + abs(end.y - start.y);
}

// Function to check if a point is within the maze bounds
bool isValidPoint(int maze[][30], int rows, int cols, struct Point point) {
    return point.x >= 0 && point.x < cols && point.y >= 0 && point.y < rows && (maze[point.y][point.x] < 3 || maze[point.y][point.x]==9);
}

// Function to check if a point is the goal point
bool isGoalPoint(struct Point point, struct Point goal) {
    return point.x == goal.x && point.y == goal.y;
}

// Function to find the index of a node in the open list based on its position
int findNodeIndex(struct Node **openList, int openCount, struct Point pos) {
    for (int i = 0; i < openCount; i++) {
        if (openList[i]->pos.x == pos.x && openList[i]->pos.y == pos.y) {
            return i;
        }
    }
    return -1;  // Node not found
}

// Function to trace back the path from the goal node to the start node
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

// Function to perform A* search
struct Point* AStar(int maze[][30], struct Point start, struct Point goal, int rows, int cols) {
    // Initialize open and closed lists
    struct Node *openList[rows * cols];
    int openCount = 0;
    bool closedList[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            closedList[i][j] = false;
        }
    }

    // Create start node and add it to the open list
    struct Node *startNode = (struct Node*)malloc(sizeof(struct Node));
    startNode->pos = start;
    startNode->gCost = 0;
    startNode->hCost = calculateHeuristic(start, goal);
    startNode->fCost = startNode->gCost + startNode->hCost;
    startNode->parent = NULL;
    openList[openCount++] = startNode;

    while (openCount > 0) {
        // Find the node with the lowest fCost in the open list
        int currentIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i]->fCost < openList[currentIndex]->fCost) {
                currentIndex = i;
            }
        }

        // Get the current node from the open list
        struct Node *currentNode = openList[currentIndex];

        // Remove the current node from the open list
        for (int i = currentIndex; i < openCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openCount--;

        // Add the current node to the closed list
        closedList[currentNode->pos.y][currentNode->pos.x] = true;

        // Check if the current node is the goal node
        if (isGoalPoint(currentNode->pos, goal)) {
            return tracePath(currentNode);
        }

        // Generate successor nodes
        struct Point successors[] = {
            {currentNode->pos.x + 1, currentNode->pos.y},
            {currentNode->pos.x - 1, currentNode->pos.y},
            {currentNode->pos.x, currentNode->pos.y + 1},
            {currentNode->pos.x, currentNode->pos.y - 1}
        };

        for (int i = 0; i < 4; i++) {
            // Check if the successor is valid
            if (isValidPoint(maze, rows, cols, successors[i]) && !closedList[successors[i].y][successors[i].x]) {
                // Calculate the cost to move to the successor node
                int gCost = currentNode->gCost + 1;
                int hCost = calculateHeuristic(successors[i], goal);
                int fCost = gCost + hCost;

                // Check if the successor is already in the open list
                int existingIndex = findNodeIndex(openList, openCount, successors[i]);
                if (existingIndex != -1 && gCost >= openList[existingIndex]->gCost) {
                    continue;
                }

                // Create a new successor node
                struct Node *successorNode = (struct Node*)malloc(sizeof(struct Node));
                successorNode->pos = successors[i];
                successorNode->gCost = gCost;
                successorNode->hCost = hCost;
                successorNode->fCost = fCost;
                successorNode->parent = currentNode;

                // Add the successor node to the open list
                openList[openCount++] = successorNode;
            }
        }
    }

    // No path found
    return NULL;
}


#endif /* SHORTESTPATH_H */
