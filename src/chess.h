#ifndef CHESS_H_
#define CHESS_H_

#define HASH_LENGTH 64
#define INVERT_CORD(n) ((8 - (n) + 7) % 8)
#define PIECE_LOOKUP(p) (piece_chars[(p)])
#define PIECE_NAME_LOOKUP(p) (piece_names[(p)])

static char piece_chars[] = " PRNBQKD";
static char* piece_names[] = {
    "N/A",
    "PAWN",
    "ROOK",
    "KNIGHT",
    "BISHIOP",
    "QUEEN",
    "KING",
    "DUCK"
};

enum piece_type {EMPTY, PAWN, ROOK, KNIGHT, BISHIOP, QUEEN, KING, DUCK};
enum column {A, B, C, D, E, F, G, H};
enum player {BLANK, WHITE, BLACK};


typedef struct game Game;
typedef struct move Move;
typedef struct piece Piece;
typedef struct cords Cords;
typedef struct move_list MoveList;

struct piece {
    int color;
    int type;
};

struct cords {
    int y; // Vertical
    int x; // Horizontal
};

struct game {
    Piece board[8][8];
    int turn;
    int castle_left_white;
    int castle_right_white;
    int castle_left_black;
    int castle_right_black;
};

struct move {
    int piece; // Allows for promotion of pawns
    Cords base_location; // starting location
    Cords new_location;  // moved location
    Cords duck_location; // Duck Placement
};

struct move_list {
    Move* move;
    MoveList* next;
};

Game* boardInvert(Game* game);
Game* gameInit(void);
Game* gameRead(char* file_name);
Game* gameWrite(Game* game);

MoveList* moveListInvert(MoveList* moveList);
MoveList* movePieces(Game* game);
MoveList* moveDuck(Game* game, MoveList* moveList);
void moveListFree(MoveList* moveList);

char* gameHash(Game* game);

#endif // CHESS_H_
