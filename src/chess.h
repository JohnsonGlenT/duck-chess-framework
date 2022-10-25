#ifndef CHESS_H_
#define CHESS_H_

#define HASH_LENGTH 64

enum piece {PAWN, ROOK, KNIGHT, BISHIOP, QUEEN, KING};
enum column {A, B, C, D, E, F, G, H};
enum player {WHITE, BLACK};

typedef struct game Game;
typedef struct move Move;

struct game{
    int board[8][8];
    int player_to_move;
};

struct move {
    int piece;
    int piece_location;
    int duck_location;
};

Game* gameRead(char* file_name);
Game* gameWrite(Game* game);
Move* getMoves(Game* game);

char* gameHash(Game* game);



#endif // CHESS_H_
