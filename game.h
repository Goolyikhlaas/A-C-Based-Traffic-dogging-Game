#ifndef GAME_H                /* Header guards to prevent double inclusion */
#define GAME_H

/* Function declarations for game.c */

/* Function to allocate memory and create a 2D array representing the game stage */
char** createGameStage(int numRows, int numCols);

/* Function to initialize the game stage with default characters for tiles, boundaries, player, and goal */
void initializeGameStage(char** gameStage, int numRows, int numCols);

/* Function to display the current state of the game stage to the console */
void showcaseGameStage(char** gameStage, int numRows, int numCols);

/* Function to update the player's position based on the input action ('w', 'a', 's', 'd'),
   check for game-over or winning conditions */
void makePlayerMove(char** gameStage, int numRows, int numCols, char playerAction, int* playerX, int* playerY, int *isGameOver, int *isGameWon);

/* Function to randomly spawn cars on even-numbered rows of the game stage */
void spawnCars(char** gameStage, int numRows, int numCols);

/* Function to update the positions of the cars on the game stage and check for collisions with the player */
void updateCarPositions(char** gameStage, int numRows, int numCols, int *playerX, int *playerY, int *isGameOver);

#endif  /* Close header guards */










