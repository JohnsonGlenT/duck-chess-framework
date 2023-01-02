#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "chess.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/* #define RED "" */
/* #define GRN "" */
/* #define YEL "" */
/* #define BLU "" */
/* #define MAG "" */
/* #define CYN "" */
/* #define WHT "" */
/* #define RESET "" */

void boardPrint(Game* game);
void moveListPrint(MoveList* moves);

#endif // CONSOLE_H_
