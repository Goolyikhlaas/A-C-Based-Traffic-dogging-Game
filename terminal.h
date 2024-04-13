/*terminal.h*/
#ifndef TERMINAL_H         /* Header guards to prevent double inclusion */
#define TERMINAL_H

/* Function declarations for terminal.c */

/* Captures a single key press without requiring the Enter key */
int getKeyPress(void);

/* Disables terminal line buffering and character echoing */
void disableBuffer(void);

/* Enables terminal line buffering and character echoing */
void enableBuffer(void);

#endif /* Close header guards */







