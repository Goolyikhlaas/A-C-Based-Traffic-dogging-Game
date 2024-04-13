#include <stdio.h>
#include <stdlib.h>
#include "game.h"  /* header file for the game */

/* Function to construct game stage */
char** createGameStage(int numRows, int numCols) {
    int rowIdx;  /* Declare index for row */
    char **gameStage = (char **)malloc(numRows * sizeof(char *));  /* Allocate memory for rows */
    for (rowIdx = 0; rowIdx < numRows; rowIdx++) {  /* Loop over each row */
        gameStage[rowIdx] = (char *)malloc(numCols * sizeof(char));  /* Allocate memory for  row's columns */
    }
    return gameStage;  /* Return the pointer to the 2D array */
}

/* Function to initialize game stage */
void initializeGameStage(char** gameStage, int numRows, int numCols) {
    int rowIdx, colIdx;  /* Declare row and column indices */
    /* loop to initialize cell of the game stage */
    for (rowIdx = 0; rowIdx < numRows; rowIdx++) {  
        for (colIdx = 0; colIdx < numCols; colIdx++) {
            /* Initialize cells based on row index */
            gameStage[rowIdx][colIdx] = (rowIdx % 2 == 0) ? '.' : ' ';
            /* Set the boundary cells to '*' */
            if (rowIdx == 0 || rowIdx == numRows - 1 || colIdx == 0 || colIdx == numCols - 1) {
                gameStage[rowIdx][colIdx] = '*';
            }
        }
    }
    /* Place the Player 'P' and Goal 'G' on the game stage */
    gameStage[1][1] = 'P';  
    gameStage[numRows - 2][numCols - 2] = 'G';  
}

/* Function to display game stage */
void showcaseGameStage(char** gameStage, int numRows, int numCols) {
    int rowIdx, colIdx;  /* Declare row and column indices */
    /* loop to print each cell of the game stage */
    for (rowIdx = 0; rowIdx < numRows; rowIdx++) {
        for (colIdx = 0; colIdx < numCols; colIdx++) {
            printf("%c", gameStage[rowIdx][colIdx]);  /* Print current cell */
        }
        printf("\n");  /* Move to the next line */
    }
}

/* Function to handle player movement */
void makePlayerMove(char** gameStage, int numRows, int numCols, char playerAction, int* playerX, int* playerY, int *isGameOver, int *isGameWon) {
    int futureX = *playerX;  /* Declare and initialize future X position */
    int futureY = *playerY;  /* Declare and initialize future Y position */
    char nextTile;  /* Declare variable to store the type of next tile */
    char tempTile;  /* Declare variable to temporarily store the tile */

    /* Update future position based on player action */
    if (playerAction == 'w') {
        futureX--;
    } else if (playerAction == 's') {
        futureX++;
    } else if (playerAction == 'a') {
        futureY--;
    } else if (playerAction == 'd') {
        futureY++;
    }

    /* Determine the type of tile at the future position */
    nextTile = gameStage[futureX][futureY];

    /* Logic for player interaction with '<' or '>' tiles */
    if (nextTile == '<' || nextTile == '>') {
        if (futureX == *playerX) {  /* Check if moving horizontally */
            /* Swap tiles */
            tempTile = gameStage[futureX][futureY];
            gameStage[futureX][futureY] = 'P';  
            gameStage[*playerX][*playerY] = tempTile;
            *playerX = futureX;  /* Update player's X position */
            *playerY = futureY;  /* Update player's Y position */
            return;  /* Return from function */
        } else {
            /* Update game state to Game Over */
            gameStage[futureX][futureY] = 'P';
            gameStage[*playerX][*playerY] = (*playerX % 2 == 0) ? '.' : ' ';
            *isGameOver = 1;  /* Set Game Over flag */
            return;  /* Return from function */
        }
    }

    /* Logic for boundary checks */
    if (futureX < 0 || futureX >= numRows || futureY < 0 || futureY >= numCols) {
        *isGameOver = 1;  /* Set Game Over flag */
        return;  /* Return from function */
    }

    /* Check if next tile is a boundary '*' */
    if (nextTile == '*') {
        return;  /* Do nothing and return */
    }

    /* Check if player reaches the goal */
    if (nextTile == 'G') {
        *isGameWon = 1;  /* Set Game Won flag */
    }

    /* Update player's position on the game stage */
    gameStage[futureX][futureY] = 'P';
    gameStage[*playerX][*playerY] = (*playerX % 2 == 0) ? '.' : ' ';
    *playerX = futureX;  /* Update player's X position */
    *playerY = futureY;  /* Update player's Y position */
}

/* Function to spawn cars on the game stage */
void spawnCars(char** gameStage, int numRows, int numCols) {
    int rowIdx, randomPos;  /* Declare row index and random position */
    char carDirection;  /* Declare variable for car direction */

    /* Loop to place cars on even rows, starts from the 3rd */
    for (rowIdx = 2; rowIdx < numRows - 1; rowIdx += 2) {
        /* Generate random position within row boundaries */
        randomPos = rand() % (numCols - 2) + 1;
        /* Determine car direction */
        carDirection = (randomPos == 1) ? '>' : (randomPos == numCols - 2) ? '<' : (rand() % 2 == 0) ? '<' : '>';
        /* Place car on the game stage */
        gameStage[rowIdx][randomPos] = carDirection;
    }
}

/* Function to update car positions */
void updateCarPositions(char** gameStage, int numRows, int numCols, int *playerX, int *playerY, int *isGameOver) {
    int rowIdx, colIdx, futureCol;  /* Declare row and column indices and future column position */
    char **tempStage = createGameStage(numRows, numCols);  /* Create a temporary game stage */
    initializeGameStage(tempStage, numRows, numCols);  /* Initialize the temporary game stage */

    tempStage[*playerX][*playerY] = 'P';  /* Update player's position on the temporary game stage */

    /* Loop to move cars on even rows starting from the 3rd row */
    for (rowIdx = 2; rowIdx < numRows - 1; rowIdx += 2) {
        for (colIdx = 1; colIdx < numCols - 1; colIdx++) {
            if (gameStage[rowIdx][colIdx] == '<' || gameStage[rowIdx][colIdx] == '>') {
                /* Calculate future column based on car direction */
                futureCol = (gameStage[rowIdx][colIdx] == '<') ? colIdx - 1 : colIdx + 1;
                if (futureCol == 1 || futureCol == numCols - 2) {
                    /* Update direction at the boundary */
                    tempStage[rowIdx][futureCol] = (gameStage[rowIdx][colIdx] == '<') ? '>' : '<';
                } else {
                    /* Move car to the new position */
                    tempStage[rowIdx][futureCol] = gameStage[rowIdx][colIdx];
                }
            }
        }
    }

    /* Update game stage based on temporary game stage */
    for (rowIdx = 2; rowIdx < numRows - 1; rowIdx += 2) {
        for (colIdx = 1; colIdx < numCols - 1; colIdx++) {
            /* Logic to move cars and check for collision */
            if (tempStage[rowIdx][colIdx] == '<' || tempStage[rowIdx][colIdx] == '>') {
                if (rowIdx != *playerX || colIdx != *playerY) {
                    gameStage[rowIdx][colIdx] = tempStage[rowIdx][colIdx];
                } else {
                    *isGameOver = 1;  /* Set Game Over flag */
                    gameStage[rowIdx][colIdx] = 'p';  
                }
            } else if (gameStage[rowIdx][colIdx] == '<' || gameStage[rowIdx][colIdx] == '>') {
                gameStage[rowIdx][colIdx] = '.';  /* Clear old car positions */
            }
        }
    }

    /* Free the allocated memory for the temporary game stage */
    for (rowIdx = 0; rowIdx < numRows; rowIdx++) {
        free(tempStage[rowIdx]);
    }
    free(tempStage);  /* Free the outer array */
}




















