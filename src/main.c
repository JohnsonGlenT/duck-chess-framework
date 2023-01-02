#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "console.h"

// TODO: add arguments
int main() {
    Game* game;
    MoveList* moves;

    game = gameInit();

    /* boardPrint(game); */

    moves = movePieces(game);
    moveListPrint(moves);
    moveListFree(moves);


    free(game);

    return 0;
}
