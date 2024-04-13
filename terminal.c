/*terminal.c*/
#include<stdio.h>            /* Standard I/O operations like printf and getchar */
#include<termios.h>          /* Terminal I/O definitions for modifying terminal attributes */
#include"terminal.h"         /* Include terminal.h for function prototypes */

/* Disables terminal line buffering and character echoing */
void disableBuffer(void) {
    struct termios mode;    /* Declare a termios structure */

    tcgetattr(0, &mode);    /* Get current terminal attributes */
    mode.c_lflag &= ~(ECHO | ICANON); /* Clear ECHO and ICANON flags */
    tcsetattr(0, TCSANOW, &mode);     /* Set new terminal attributes */
}

/* Enables terminal line buffering and character echoing */
void enableBuffer(void) {
    struct termios mode;    /* Declare a termios structure */

    tcgetattr(0, &mode);    /* Get current terminal attributes */
    mode.c_lflag |= (ECHO | ICANON);  /* Set ECHO and ICANON flags */
    tcsetattr(0, TCSANOW, &mode);     /* Set new terminal attributes */
}

/* Captures a single key press without requiring the Enter key */
int getKeyPress(void) {
    int key;                /* Declare an integer to hold the key pressed */

    disableBuffer();        /* Disable terminal buffering */
    key = getchar();        /* Read a single character */
    enableBuffer();         /* Enable terminal buffering */

    return key;             /* Return the key pressed */
}











