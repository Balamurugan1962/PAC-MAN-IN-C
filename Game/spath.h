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

#endif /* SHORTESTPATH_H */
