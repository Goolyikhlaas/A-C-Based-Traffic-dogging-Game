#include "terminal.h"  /* Include terminal.h for terminal-related functions */
#include "game.h"      /* Include game.h for game-related functions */
#include <stdio.h>     /* Include standard I/O functions like printf */
#include <stdlib.h>    /* Include standard library functions like system and malloc */

int main(int argc, char *argv[]) {
    int numRows, numCols, playerX, playerY, isGameOver, isGameWon, loopIndex;
    char **gameStage;  /* Declare gameStage here */
    char playerAction;

    /* Check if the number of command-line arguments is correct */
    if (argc != 3) {
        printf("Usage: ./traffic <map_row> <map_col>\n");
        return 0;
    }

    numRows = atoi(argv[1]);
    numCols = atoi(argv[2]);

    /* Validate the command-line arguments */
    if (numRows < 3 || numRows % 2 == 0 || numCols < 5) {
        printf("Invalid arguments. Ensure map_row is odd and >= 3, and map_col >= 5.\n");
        return 0;
    }

    playerX = 1;
    playerY = 1;
    isGameOver = 0;
    isGameWon = 0;

    gameStage = createGameStage(numRows, numCols);  /* Initialize gameStage here */
    initializeGameStage(gameStage, numRows, numCols);
    spawnCars(gameStage, numRows, numCols);

    /* Main game loop */
    while (!isGameOver && !isGameWon) {
        system("clear");
        showcaseGameStage(gameStage, numRows, numCols);

        printf("Press w to move up\n");
        printf("Press s to move down\n");
        printf("Press a to move left\n");
        printf("Press d to move right\n");

        playerAction = getKeyPress();
        makePlayerMove(gameStage, numRows, numCols, playerAction, &playerX, &playerY, &isGameOver, &isGameWon);
        updateCarPositions(gameStage, numRows, numCols, &playerX, &playerY, &isGameOver);

        if (isGameWon) {
            system("clear");
            showcaseGameStage(gameStage, numRows, numCols);
            printf("You Win!\n");
            break;
        }

        if (isGameOver) {
            system("clear");
            showcaseGameStage(gameStage, numRows, numCols);
            printf("Game Over!\n");
            break;
        }
    }

    /* Free the dynamically allocated memory for game stage */
    for (loopIndex = 0; loopIndex < numRows; loopIndex++) {
        free(gameStage[loopIndex]);
    }
    free(gameStage);

    return 0;
}


















