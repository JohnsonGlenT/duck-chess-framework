#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "console.h"
#include "custom.h"

void boardPrint(Game* game) {
    for (int x = 7; x >= 0; x--) {
        printf(WHT " |");
        for (int y = 7; y >= 0; y--) {
            if (game->board[x][y].type != EMPTY) {
                game->board[x][y].color == WHITE ?
                    printf(WHT):
                    printf(RED);
            }
            printf(" %c ", PIECE_LOOKUP(game->board[x][y].type));
            printf(WHT "|");
        }
        printf("\n");

        printf(WHT " -");
        for (int y = 0; y < 8; y++) {
            printf(WHT "----");
        }
        printf(WHT "- ");

        printf("\n");
    }
    printf(RESET "\n\n");
}

void moveListPrint(MoveList* moves) {
    for (MoveList* move = moves; move->move != NULL; move = move->next) {
        Move m = (*move->move);
        printf("Piece: %s\n", PIECE_NAME_LOOKUP(m.piece));
        printf("Base Location: (%d,%d)\n", m.base_location.y, m.base_location.x);
        printf("New  Location: (%d,%d)\n", m.new_location.y, m.new_location.x);
        printf("Duck Location: N/A\n\n");

    }
}
