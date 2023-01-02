#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "console.h"

Game* boardInvert(Game* game) {
    Piece newBoard[8][8];
    memset(newBoard, 0, sizeof(Piece)*8*8);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            memcpy(&newBoard[INVERT_CORD(x)][INVERT_CORD(y)],
                   &game->board[x][y], sizeof(Piece));
        }
    }

    memcpy(game->board, newBoard, sizeof(Piece)*8*8);
    return game;
}

Game* gameInit(void) {
    Game* game = malloc(sizeof(Game));

    game->turn = WHITE;
    game->castle_left_white = 1;
    game->castle_left_black = 1;
    game->castle_right_white = 1;
    game->castle_right_black = 1;
    memset(game->board, 0, sizeof(Piece)*8*8);

    for (int i = 0; i < 8; i++) {
        game->board[1][i].color = WHITE;
        game->board[1][i].type = PAWN;

        game->board[6][i].color = BLACK;
        game->board[6][i].type = PAWN;
    }

    game->board[0][0].color = WHITE;
    game->board[0][0].type = ROOK;

    game->board[7][0].color = BLACK;
    game->board[7][0].type = ROOK;

    game->board[0][7].color = WHITE;
    game->board[0][7].type = ROOK;

    game->board[7][7].color = BLACK;
    game->board[7][7].type = ROOK;

    game->board[0][1].color = WHITE;
    game->board[0][1].type = KNIGHT;

    game->board[7][1].color = BLACK;
    game->board[7][1].type = KNIGHT;

    game->board[0][6].color = WHITE;
    game->board[0][6].type = KNIGHT;

    game->board[7][6].color = BLACK;
    game->board[7][6].type = KNIGHT;

    game->board[0][2].color = WHITE;
    game->board[0][2].type = BISHIOP;

    game->board[7][2].color = BLACK;
    game->board[7][2].type = BISHIOP;

    game->board[0][5].color = WHITE;
    game->board[0][5].type = BISHIOP;

    game->board[7][5].color = BLACK;
    game->board[7][5].type = BISHIOP;

    game->board[0][3].color = WHITE;
    game->board[0][3].type = KING;

    game->board[7][3].color = BLACK;
    game->board[7][3].type = KING;

    game->board[0][4].color = WHITE;
    game->board[0][4].type = QUEEN;

    game->board[7][4].color = BLACK;
    game->board[7][4].type = QUEEN;

    return game;
}

Game* gameRead(char* file_name) {

    return NULL;
}

Game* gameWrite(Game* game) {

    return NULL;
}

MoveList* moveListInvert(MoveList* moveList) {
    MoveList* m = moveList;
    while (m->move != NULL) {
        m->move->base_location.x = INVERT_CORD(m->move->base_location.x);
        m->move->new_location.x = INVERT_CORD(m->move->new_location.x);

        m = m->next;
    }

    return moveList;
}

MoveList* movePieces(Game* game) {
    MoveList* moves = malloc(sizeof(MoveList));
    MoveList* head = moves;
    moves->move = NULL;
    moves->next = NULL;

    // invert game orrietation
    if (game->turn == BLACK) { boardInvert(game); }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            /* printf("debug: checking x:%d y:%d\n", x, y); */
            Piece square = game->board[x][y];

            if (game->turn != square.color) { continue; }
            switch (square.type) {
                case EMPTY:
                case DUCK:
                    break;
                case PAWN:
                    // left and right square move check
                    if (game->board[x+1][y+1].color != BLANK &&
                        game->board[x+1][y+1].color != game->turn) {
                        if (x + 1 == 7) {
                            for (int piece = ROOK; piece < KING; piece++) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x+1;
                                moves->move->new_location.y = y+1;
                                moves->move->piece = piece;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                            }
                        } else {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    if (game->board[x+1][y-1].color != BLANK &&
                        game->board[x+1][y-1].color != game->turn) {
                        if (x + 1 == 7) {
                            for (int piece = ROOK; piece < KING; piece++) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x+1;
                                moves->move->new_location.y = y-1;
                                moves->move->piece = piece;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                            }
                        } else {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    if (game->board[x+1][y].color == BLANK) {
                        moves->move = malloc(sizeof(Move));
                        moves->move->base_location.x = x;
                        moves->move->base_location.y = y;

                        moves->move->new_location.x = x+1;
                        moves->move->new_location.y = y;
                        moves->move->piece = square.type;

                        moves->next = malloc(sizeof(MoveList));
                        moves = moves->next;
                        if (x == 1 && game->board[x+2][y].color == BLANK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+2;
                            moves->move->new_location.y = y;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }

                    break;
                case KNIGHT:
                    // x - 2 y + 1
                    if (x - 2 >= 0 && y + 1 < 8)  {
                        if (game->board[x-2][y+1].color != game->turn &&
                            game->board[x-2][y+1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-2;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x - 2 y - 1
                    if (x - 2 >= 0 && y - 1 >= 0)  {
                        if (game->board[x-2][y-1].color != game->turn &&
                            game->board[x-2][y-1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-2;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x - 1 y + 2
                    if (x - 1 >= 0 && y + 2 < 8)  {
                        if (game->board[x-1][y+2].color != game->turn &&
                            game->board[x-1][y+2].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-1;
                            moves->move->new_location.y = y+2;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x - 1 y - 2
                    if (x - 1 >= 0 && y - 2 >= 0)  {
                        if (game->board[x-1][y-2].color != game->turn &&
                            game->board[x-1][y-2].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-1;
                            moves->move->new_location.y = y-2;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x + 2 y + 1
                    if (x + 2 < 8 && y + 1 < 8)  {
                        if (game->board[x+2][y+1].color != game->turn &&
                            game->board[x+2][y+1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+2;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x + 2 y - 1
                    if (x + 2 < 8 && y - 1 >= 0)  {
                        if (game->board[x+2][y-1].color != game->turn &&
                            game->board[x+2][y-1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+2;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x + 1 y + 2
                    if (x + 1 < 8 && y + 2 < 8)  {
                        if (game->board[x+1][y+2].color != game->turn &&
                            game->board[x+1][y+2].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y+2;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    // x + 1 y - 2
                    if (x + 1 < 8 && y - 2 >= 0)  {
                        if (game->board[x+1][y-2].color != game->turn &&
                            game->board[x+1][y-2].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y-2;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }
                    break;
                case QUEEN:
                case ROOK:
                    // left
                    for (int i = x - 1; i >= 0; i--) {
                        if (game->board[i][y].type == DUCK ||
                            game->board[i][y].color == game->turn) {
                            break;
                        }
                        moves->move = malloc(sizeof(Move));
                        moves->move->base_location.x = x;
                        moves->move->base_location.y = y;

                        moves->move->new_location.x = i;
                        moves->move->new_location.y = y;
                        moves->move->piece = square.type;

                        moves->next = malloc(sizeof(MoveList));
                        moves = moves->next;
                        if (game->board[i][y].color != BLANK) {
                            break;
                        }
                    }
                    // right
                    for (int i = x + 1; i >= 0; i++) {
                        if (game->board[i][y].type == DUCK ||
                            game->board[i][y].color == game->turn) {
                            break;
                        }
                        moves->move = malloc(sizeof(Move));
                        moves->move->base_location.x = x;
                        moves->move->base_location.y = y;

                        moves->move->new_location.x = i;
                        moves->move->new_location.y = y;
                        moves->move->piece = square.type;

                        moves->next = malloc(sizeof(MoveList));
                        moves = moves->next;
                        if (game->board[i][y].color != BLANK) {
                            break;
                        }
                    }
                    // up
                    for (int i = y + 1; i < 8; i++) {
                        if (game->board[x][i].type == DUCK ||
                            game->board[x][i].color == game->turn) {
                            break;
                        }
                        moves->move = malloc(sizeof(Move));
                        moves->move->base_location.x = x;
                        moves->move->base_location.y = y;

                        moves->move->new_location.x = i;
                        moves->move->new_location.y = y;
                        moves->move->piece = square.type;

                        moves->next = malloc(sizeof(MoveList));
                        moves = moves->next;
                        if (game->board[x][i].color != BLANK) {
                            break;
                        }
                    }
                    // down
                    for (int i = y - 1; i >= 0; i--) {
                        if (game->board[x][i].type == DUCK ||
                            game->board[x][i].color == game->turn) {
                            break;
                        }
                        moves->move = malloc(sizeof(Move));
                        moves->move->base_location.x = x;
                        moves->move->base_location.y = y;

                        moves->move->new_location.x = i;
                        moves->move->new_location.y = y;
                        moves->move->piece = square.type;

                        moves->next = malloc(sizeof(MoveList));
                        moves = moves->next;
                        if (game->board[x][i].color != BLANK) {
                            break;
                        }
                    }
                    // If queen add bishiop moves
                    if (square.type == ROOK) { break; }
                case BISHIOP:
                    // if true, path is blocked
                    NULL; // LSP Correction
                    int up_left = 0;
                    int up_right = 0;
                    int down_left = 0;
                    int down_right = 0;
                    for (int i = 1; i < 8; i++) {
                        if (x + i < 8 && y - i >= 0 && !up_left) {
                            // check empty pos
                            if (game->board[x+i][y-i].color == game->turn ||
                                game->board[x+i][y-i].type == DUCK) {
                                up_left = 1;
                            } else {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x+i;
                                moves->move->new_location.y = y-i;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                                if (game->board[x+i][y-i].color != BLANK) {
                                    up_left = 1;
                                }
                            }
                        }
                        if (x + i < 8 && y + i < 8 && !up_right) {
                            // check empty pos
                            if (game->board[x+i][y+i].color == game->turn ||
                                game->board[x+i][y+i].type == DUCK) {
                                up_right = 1;
                            } else {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x+i;
                                moves->move->new_location.y = y+i;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                                if (game->board[x+i][y+i].color != BLANK) {
                                    up_right = 1;
                                }
                            }
                        }
                        if (x - i >= 0 && y - i >= 0 && !down_left) {
                            // check empty pos
                            if (game->board[x-i][y-i].color == game->turn ||
                            game->board[x-i][y-i].type == DUCK) {
                                down_left = 1;
                            } else {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x-i;
                                moves->move->new_location.y = y-i;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                                if (game->board[x-i][y-i].color != BLANK) {
                                    down_left = 1;
                                }
                            }
                        }
                        if (x - i >= 0 && y + i < 8 && !down_right) {
                            // check empty pos
                            if (game->board[x-i][y+i].color == game->turn ||
                                game->board[x-i][y+i].type == DUCK) {
                                down_right = 1;
                            } else {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x-i;
                                moves->move->new_location.y = y+i;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                                if (game->board[x-i][y+i].color != BLANK) {
                                    down_right = 1;
                                }
                            }
                        }
                        if (up_left && up_right && down_left && down_right) {
                            break;
                        }
                    }
                    break;
                case KING:
                    if (x + 1 < 8) {
                        if (game->board[x+1][y].color != game->turn &&
                            game->board[x+1][y].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (x + 1 < 8 && y +1 < 8) {
                        if (game->board[x+1][y+1].color != game->turn &&
                            game->board[x+1][y+1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (y + 1 < 8) {
                        if (game->board[x][y+1].color != game->turn &&
                            game->board[x][y+1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (x - 1 >= 0 && y + 1 < 8) {
                        if (game->board[x-1][y+1].color != game->turn &&
                            game->board[x-1][y+1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-1;
                            moves->move->new_location.y = y+1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (x - 1 >= 0) {
                        if (game->board[x-1][y].color != game->turn &&
                            game->board[x-1][y].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-1;
                            moves->move->new_location.y = y;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (x - 1 >= 0 && y - 1 >= 0) {
                        if (game->board[x-1][y-1].color != game->turn &&
                            game->board[x-1][y-1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x-1;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (y - 1 >= 0) {
                        if (game->board[x][y-1].color != game->turn &&
                            game->board[x][y-1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;

                        }
                    }
                    if (x + 1 > 8 && y - 1 >= 0) {
                        if (game->board[x+1][y-1].color != game->turn &&
                            game->board[x+1][y-1].type != DUCK) {
                            moves->move = malloc(sizeof(Move));
                            moves->move->base_location.x = x;
                            moves->move->base_location.y = y;

                            moves->move->new_location.x = x+1;
                            moves->move->new_location.y = y-1;
                            moves->move->piece = square.type;

                            moves->next = malloc(sizeof(MoveList));
                            moves = moves->next;
                        }
                    }

                    // TODO: Castling
                    int can_castle_left = 1;
                    int can_castle_right = 1;
                    if (game->turn == WHITE) {
                        if (game->castle_right_white) {
                            for (int i = 0; y + i < 7; i++) {
                                if (game->board[x][y+i].type != EMPTY) {
                                    can_castle_right = 0;
                                    break;
                                }
                            }
                            if (can_castle_right) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x;
                                moves->move->new_location.y = y+2;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                            }
                        }
                        if (game->castle_left_white) {
                            for (int i = 0; y - i > 0; i--) {
                                if (game->board[x][y-i].type != EMPTY) {
                                    can_castle_left = 0;
                                    break;
                                }
                            }
                            if (can_castle_left) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x;
                                moves->move->new_location.y = y-2;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;

                            }
                        }
                    } else {
                        if (game->castle_right_black) {
                            for (int i = 0; y + i < 7; i++) {
                                if (game->board[x][y+i].type != EMPTY) {
                                    can_castle_right = 0;
                                    break;
                                }
                            }
                            if (can_castle_right) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x;
                                moves->move->new_location.y = y + 2;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;

                            }
                        }
                        if (game->castle_left_black) {
                            for (int i = 0; y - i > 0; i--) {
                                if (game->board[x][y-i].type != EMPTY) {
                                    can_castle_left = 0;
                                    break;
                                }
                            }
                            if (can_castle_left) {
                                moves->move = malloc(sizeof(Move));
                                moves->move->base_location.x = x;
                                moves->move->base_location.y = y;

                                moves->move->new_location.x = x;
                                moves->move->new_location.y = y - 2;
                                moves->move->piece = square.type;

                                moves->next = malloc(sizeof(MoveList));
                                moves = moves->next;
                            }
                        }
                    }
                    break;
                default:
                    fprintf(stderr, "Malformed Game Data, exiting\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    // return game correct orrientation
    if (game->turn == BLACK) {
        boardInvert(game);
        moveListInvert(head);
    }

    if (head->move == NULL) {
        free(head);
        head = NULL;
    }

    return head;
}

MoveList* moveDuck(Game* game, MoveList* moveList) {
    return moveList;
}

void moveListFree(MoveList* moveList) {
    MoveList* m = moveList;
    MoveList* tmp;
    while (m != NULL) {
        tmp = m;
        m = m->next;
        free(tmp->move);
        free(tmp);
    }
}

char* gameHash(Game* game) {

    return NULL;
}
